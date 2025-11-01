## Assigment - 02

Press Start and open “x64 Native Tools Command Prompt for VS 2022” (cmd.exe)
or “Developer PowerShell for VS 2022”.

Statement - 1
```bash
cl ".\practical-06\practical-06-1.c" /I "C:\Program Files (x86)\Microsoft SDKs\MPI\Include" /Fo".\practical-06\practical-06-1.obj" /Fe".\practical-06\practical-06-1.exe" /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib
mpiexec -n 10 .\practical-06\practical-06-1.exe 
```
Statement - 2
```bash
cl ".\practical-06\practical-06-2.c" /I "C:\Program Files (x86)\Microsoft SDKs\MPI\Include" /Fo".\practical-06\practical-06-2.obj" /Fe".\practical-06\practical-06-2.exe" /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib
mpiexec -n 5 .\practical-06\practical-06-2.exe 
```
Statement - 3
```bash
cl ".\practical-06\practical-06-3.c" /I "C:\Program Files (x86)\Microsoft SDKs\MPI\Include" /Fo".\practical-06\practical-06-3.obj" /Fe".\practical-06\practical-06-3.exe" /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib
mpiexec -n 2 .\practical-06\practical-06-3.exe 
```
Statement - 4
```bash
cl ".\practical-06\practical-06-4.c" /I "C:\Program Files (x86)\Microsoft SDKs\MPI\Include" /Fo".\practical-06\practical-06-4.obj" /Fe".\practical-06\practical-06-4.exe" /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib
mpiexec -n 4 .\practical-06\practical-06-4.exe 
```
Statement - 5
```bash
cl ".\practical-06\practical-06-5.c" /I "C:\Program Files (x86)\Microsoft SDKs\MPI\Include" /Fo".\practical-06\practical-06-5.obj" /Fe".\practical-06\practical-06-5.exe" /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib
mpiexec -n 2 .\practical-06\practical-06-5.exe 
```
