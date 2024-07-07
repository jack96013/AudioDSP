'''
Author       : TZU-CHIEH, HSU
Mail         : j.k96013@gmail.com
Department   : ECIE Lab, NTUT
Date         : 2024-07-06 13:50:50
LastEditTime : 2024-07-06 14:47:16
Description  : 
'''
import os
import subprocess
Import("env")

print("Current CLI targets", COMMAND_LINE_TARGETS)
print("Current Build targets", BUILD_TARGETS)


def before_task():
    print("Running pre-build commands...")

    # CD 到 .\src\AudioDSP
    audio_dsp_project_path = os.path.join(env['PROJECT_DIR'], 'src', 'AudioDSP')

    # 臨時更改 PowerShell 執行原則並執行腳本
    ps_command = f"""
    Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass -Force;
    cd {audio_dsp_project_path}
    ./DSP_Parameter_generator.ps1;
    """
    result = subprocess.run(["powershell.exe", "-Command", ps_command], capture_output=True, text=True)

    # 打印 PowerShell 腳本的輸出
    print(result.stdout)
    if result.returncode != 0:
        print(result.stderr)

        

        

before_task()

def before_buildfs(source, target, env):
    print("before_buildfs")
    
    # do some actions


    
# 註冊 hook

env.AddPreAction("$BUILD_DIR/${ESP32_FS_IMAGE_NAME}.bin", before_buildfs) 