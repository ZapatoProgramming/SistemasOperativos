@echo off
set /p variable="Ingrese un valor:"
echo La computadora se apagara en %variable% segundos
shutdown /s /t  %variable%
set /a x=10
set /a z=%x%-%variable%
if %z% lss 0 (
timeout 10
shutdown /a
echo te la creiste wexddddd
) else (
set /a variable = %variable% - 1
timeout %variable%
shutdown /a
echo te la creiste wexddddd
)
pause