import sys
import os
import mido  # 修复 MidiFile 未定义问题
from PyQt5.QtWidgets import (
    QApplication, QWidget, QLabel, QLineEdit,
    QPushButton, QFileDialog, QVBoxLayout, QMessageBox
)

NOTE_DURATIONS = {
    4.0: "whole",
    3.0: "dotted half",
    2.0: "half",
    1.5: "dotted quater",
    1.0: "quater",
    0.75: "dotted quaver",
    0.5: "quaver",
    0.25: "quaver /2"
}

BASE_NOTES = {
    69: "A4", 70: "A4sharp", 71: "B4",
    60: "C4", 61: "C4sharp", 62: "D4", 63: "D4sharp", 64: "E4",
    65: "F4", 66: "F4sharp", 67: "G4", 68: "G4sharp",
    57: "A3", 58: "A3sharp", 59: "B3"
}

def quantize(duration_beats):
    best = min(NOTE_DURATIONS.keys(), key=lambda x: abs(x - duration_beats))
    err = abs(best - duration_beats)
    if err > 0.1:
        if duration_beats < min(NOTE_DURATIONS.keys()):
            smallest = min(NOTE_DURATIONS.keys())
            ratio = duration_beats / smallest
            return NOTE_DURATIONS[smallest] + f" /{int(round(1/ratio))}", ratio
        elif duration_beats > max(NOTE_DURATIONS.keys()):
            largest = max(NOTE_DURATIONS.keys())
            ratio = duration_beats / largest
            return NOTE_DURATIONS[largest] + f" *{int(round(ratio))}", ratio
        else:
            return None, duration_beats  # 无法量化，返回 None 和原始时值
    return NOTE_DURATIONS[best], duration_beats / best

def pitch_to_text(midi_note):
    for base in BASE_NOTES:
        for i in range(-3, 4):
            if base + i * 12 == midi_note:
                tag = ""
                if i > 0: tag = " octup" * i
                elif i < 0: tag = " octdown" * (-i)
                return BASE_NOTES[base] + tag
    return f"MIDI{midi_note}"

def process_midi(path, output_path=None, bpm_override=None, beat_sig="4/4", analyze_only=False):
    midi = mido.MidiFile(path)
    ticks_per_beat = midi.ticks_per_beat
    tempo = 500000  # default 120 bpm

    note_tracks = []
    for i, track in enumerate(midi.tracks):
        if any(msg.type in ("note_on", "note_off") for msg in track):
            note_tracks.append(track)

    if len(note_tracks) != 1:
        raise ValueError("MIDI文件应仅含一条音轨含音符")

    events = []
    track = note_tracks[0]
    time = 0
    notes_on = {}
    for msg in track:
        time += msg.time
        if msg.type == 'set_tempo':
            tempo = msg.tempo
        elif msg.type == 'note_on' and msg.velocity > 0:
            notes_on[msg.note] = time
        elif (msg.type == 'note_off') or (msg.type == 'note_on' and msg.velocity == 0):
            if msg.note not in notes_on:
                continue  # 忽略意外note_off
            start = notes_on.pop(msg.note)
            duration = time - start
            events.append((start, msg.note, duration))

    if any(events[i][0] == events[i+1][0] for i in range(len(events)-1)):
        raise ValueError("发现复音，MIDI应为单音轨单复音")

    bpm = mido.tempo2bpm(tempo)
    if bpm_override:
        bpm = bpm_override

    if analyze_only:
        return round(bpm, 2), beat_sig

    beat = 60.0 / bpm
    events.sort()

    lines = [f"// bpm={int(round(bpm))} beat={beat_sig}"]
    current_bar_beat = 0
    bar_limit = int(beat_sig.split('/')[0])
    line = ""
    prev_end = 0

    for start, note, duration_ticks in events:
        duration_beats = duration_ticks / ticks_per_beat
        gap_beats = (start - prev_end) / ticks_per_beat

        if gap_beats > 0.05:
            rest_label, ratio = quantize(gap_beats)
            if rest_label is None:
                dur_txt = f"{gap_beats:.2f}*beat"
            else:
                dur_txt = rest_label
            line += f"note(rest, {dur_txt}); "
            current_bar_beat += gap_beats

        duration_label, ratio = quantize(duration_beats)
        pitch = pitch_to_text(note)
        if duration_label is None:
            dur_txt = f"{duration_beats:.2f}*beat"
        else:
            dur_txt = duration_label
        line += f"note({pitch}, {dur_txt}); "
        current_bar_beat += duration_beats
        prev_end = start + duration_ticks

        if current_bar_beat >= bar_limit:
            lines.append(line.strip())
            line = ""
            current_bar_beat = 0

    if line:
        lines.append(line.strip())

    with open(output_path, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))

class MidiToTextApp(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("MIDI 转换器")
        self.midi_path = None

        self.bpm_label = QLabel("BPM:")
        self.bpm_input = QLineEdit("150")

        self.time_label = QLabel("拍号 (如 4/4):")
        self.time_input = QLineEdit("4/4")

        self.load_button = QPushButton("加载 MIDI 文件")
        self.load_button.clicked.connect(self.load_midi)

        self.convert_button = QPushButton("转换为文本")
        self.convert_button.clicked.connect(self.convert)

        layout = QVBoxLayout()
        layout.addWidget(self.bpm_label)
        layout.addWidget(self.bpm_input)
        layout.addWidget(self.time_label)
        layout.addWidget(self.time_input)
        layout.addWidget(self.load_button)
        layout.addWidget(self.convert_button)
        self.setLayout(layout)

    def load_midi(self):
        path, _ = QFileDialog.getOpenFileName(self, "选择 MIDI 文件", "", "MIDI Files (*.mid *.midi)")
        if path:
            self.midi_path = path
            try:
                bpm, time_sig = process_midi(path, analyze_only=True)
                self.bpm_input.setText(str(bpm))
                self.time_input.setText(time_sig)
                QMessageBox.information(self, "成功", "MIDI 文件加载成功")
            except Exception as e:
                QMessageBox.critical(self, "错误", str(e))

    def convert(self):
        if not self.midi_path:
            QMessageBox.warning(self, "提示", "请先加载 MIDI 文件")
            return

        try:
            bpm = float(self.bpm_input.text())
            beat = self.time_input.text()
            output_path = os.path.join(os.getcwd(), "output.txt")
            process_midi(self.midi_path, output_path=output_path, bpm_override=bpm, beat_sig=beat)
            QMessageBox.information(self, "完成", f"转换完成，已保存为：\n{output_path}")
        except Exception as e:
            QMessageBox.critical(self, "转换错误", str(e))

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MidiToTextApp()
    window.show()
    sys.exit(app.exec_())
