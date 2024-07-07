@echo off
chcp 65001 > nul
setlocal enabledelayedexpansion

rem 檢查是否提供了目錄參數
if "%~1"=="" (
    echo 請提供要壓縮的資料夾路徑。
    echo 用法: minify.bat [資料夾路徑]
    exit /b 1
)

rem 設定目標目錄變數
set TARGET_DIR=%~1
set MIN_DIR=%TARGET_DIR%\min

rem 創建壓縮文件的目標目錄
if not exist "%MIN_DIR%" (
    mkdir "%MIN_DIR%"
)

rem 壓縮目標目錄中的所有 HTML 檔案
for /r "%TARGET_DIR%" %%f in (*.html) do (
    echo 壓縮 %%f
    start html-minifier --collapse-whitespace --remove-comments --minify-css true --minify-js true -o "%MIN_DIR%\%%~nxf" %%f
)
echo aa

rem 壓縮目標目錄中的所有 CSS 檔案
for /r "%TARGET_DIR%" %%f in (*.css) do (
    echo 壓縮 CSS %%f
    start cleancss -o "%MIN_DIR%\%%~nxf" %%f
)

rem 壓縮目標目錄中的所有 JS 檔案
for /r "%TARGET_DIR%" %%f in (*.js) do (
    echo 壓縮 %%f
    start uglifyjs %%f -o "%MIN_DIR%\%%~nxf"
)

endlocal
echo 完成壓縮所有 HTML、CSS 和 JS 檔案。
pause