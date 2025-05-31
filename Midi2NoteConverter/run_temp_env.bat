@echo off
setlocal

REM 创建临时虚拟环境
set VENV_DIR=.\_temp_env
python -m venv %VENV_DIR%

REM 激活虚拟环境
call %VENV_DIR%\Scripts\activate.bat

REM 安装依赖
pip install --upgrade pip >nul
pip install -r requirements.txt

REM 运行主程序
python Midi2NoteConverter.py

REM 退出后清理虚拟环境
call %VENV_DIR%\Scripts\deactivate.bat
rmdir /s /q %VENV_DIR%

endlocal