rem ------------------------- GizmoBase libs --------------------------------

rmdir /S /Q GizmoBase\include
mkdir GizmoBase\include
xcopy "%GIZMOSDK%\GizmoBase\include\*.h" GizmoBase\include


rmdir /S /Q GizmoBase\libs\windows\x64

mkdir  GizmoBase\libs\windows\x64\Debug
copy "%CSW%\ws\vs17\CSW\x64\Debug\gzBase*.lib" GizmoBase\libs\windows\x64\Debug
copy "%CSW%\ws\vs17\CSW\x64\Debug\gzBase*.dll" GizmoBase\libs\windows\x64\Debug

mkdir  GizmoBase\libs\windows\x64\Release
copy "%CSW%\ws\vs17\CSW\x64\Release\gzBase*.lib" GizmoBase\libs\windows\x64\Release
copy "%CSW%\ws\vs17\CSW\x64\Release\gzBase*.dll" GizmoBase\libs\windows\x64\Release


rem ------------------------- Gizmo3D libs --------------------------------

rmdir /S /Q Gizmo3D\include
mkdir Gizmo3D\include
xcopy "%GIZMOSDK%\Gizmo3D\include\*.h" Gizmo3D\include


rmdir /S /Q Gizmo3D\libs\windows\x64
mkdir  Gizmo3D\libs\windows\x64\Debug

copy "%CSW%\ws\vs17\CSW\x64\Debug\gzImage*.lib" Gizmo3D\libs\windows\x64\Debug
copy "%CSW%\ws\vs17\CSW\x64\Debug\gzImage*.dll" Gizmo3D\libs\windows\x64\Debug
copy "%CSW%\ws\vs17\CSW\x64\Debug\gzGraph*.lib" Gizmo3D\libs\windows\x64\Debug
copy "%CSW%\ws\vs17\CSW\x64\Debug\gzGraph*.dll" Gizmo3D\libs\windows\x64\Debug
copy "%CSW%\ws\vs17\CSW\x64\Debug\gzDb*.lib" Gizmo3D\libs\windows\x64\Debug
copy "%CSW%\ws\vs17\CSW\x64\Debug\gzDb*.dll" Gizmo3D\libs\windows\x64\Debug
copy "%CSW%\ws\vs17\CSW\x64\Debug\gzSystem*.lib" Gizmo3D\libs\windows\x64\Debug
copy "%CSW%\ws\vs17\CSW\x64\Debug\gzSystem*.dll" Gizmo3D\libs\windows\x64\Debug


mkdir  Gizmo3D\libs\windows\x64\Release

copy "%CSW%\ws\vs17\CSW\x64\Release\gzImage*.lib" Gizmo3D\libs\windows\x64\Release
copy "%CSW%\ws\vs17\CSW\x64\Release\gzImage*.dll" Gizmo3D\libs\windows\x64\Release
copy "%CSW%\ws\vs17\CSW\x64\Release\gzGraph*.lib" Gizmo3D\libs\windows\x64\Release
copy "%CSW%\ws\vs17\CSW\x64\Release\gzGraph*.dll" Gizmo3D\libs\windows\x64\Release
copy "%CSW%\ws\vs17\CSW\x64\Release\gzDb*.lib" Gizmo3D\libs\windows\x64\Release
copy "%CSW%\ws\vs17\CSW\x64\Release\gzDb*.dll" Gizmo3D\libs\windows\x64\Release
copy "%CSW%\ws\vs17\CSW\x64\Release\gzSystem*.lib" Gizmo3D\libs\windows\x64\Release
copy "%CSW%\ws\vs17\CSW\x64\Release\gzSystem*.dll" Gizmo3D\libs\windows\x64\Release

rem ------------------------- Coordinate libs --------------------------------

rmdir /S /Q Coordinate\include
mkdir Coordinate\include
xcopy "%GIZMOSDK%\plugins\gzCoordinate\include\*.h" Coordinate\include

rmdir /S /Q Coordinate\libs\windows\x64

mkdir  Coordinate\libs\windows\x64\Debug
copy "%CSW%\ws\vs17\CSW\x64\Debug\gzCoordinate*.lib" Coordinate\libs\windows\x64\Debug
copy "%CSW%\ws\vs17\CSW\x64\Debug\gzCoordinate*.dll" Coordinate\libs\windows\x64\Debug

mkdir  Coordinate\libs\windows\x64\Release
copy "%CSW%\ws\vs17\CSW\x64\Release\gzCoordinate*.lib" Coordinate\libs\windows\x64\Release
copy "%CSW%\ws\vs17\CSW\x64\Release\gzCoordinate*.dll" Coordinate\libs\windows\x64\Release

rem ------------------------- CSW SceneManager libs --------------------------------

rmdir /S /Q SceneManager\include
mkdir SceneManager\include
xcopy "%CSW%\source\Presentation\Streaming\Map Streamer\cswSceneManager\include\*.h" SceneManager\include

rmdir /S /Q SceneManager\libs\windows\x64

mkdir SceneManager\libs\windows\x64\Debug
copy "%CSW%\ws\vs17\CSW\x64\Debug\cswSceneManager*.lib" SceneManager\libs\windows\x64\Debug
copy "%CSW%\ws\vs17\CSW\x64\Debug\cswSceneManager*.dll" SceneManager\libs\windows\x64\Debug

mkdir SceneManager\libs\windows\x64\Release
copy "%CSW%\ws\vs17\CSW\x64\Release\cswSceneManager*.lib" SceneManager\libs\windows\x64\Release
copy "%CSW%\ws\vs17\CSW\x64\Release\cswSceneManager*.dll" SceneManager\libs\windows\x64\Release