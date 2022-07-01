set PROGRAM= "%~1"

set OUT= "%TEMP%\decout.txt"

echo normal input
%PROGRAM% "10" > %OUT% || goto err
fc.exe %OUT% Copy-out.txt || goto err

echo letter input
%PROGRAM% "v" > %OUT% || goto err
fc.exe %OUT% Letter-out.txt || goto err

echo symbol input
%PROGRAM% "%" > %OUT% || goto err
fc.exe %OUT% Symb-out.txt || goto err

echo empty input
%PROGRAM% "" > %OUT% || goto err
fc.exe %OUT% Empty-out.txt || goto err


echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1