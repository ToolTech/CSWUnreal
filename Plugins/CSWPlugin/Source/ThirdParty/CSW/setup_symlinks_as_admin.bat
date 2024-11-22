rem ------------------------- GizmoBase libs --------------------------------

rmdir /S /Q GizmoBase\include
mklink /D GizmoBase\include "%GIZMOSDK%\GizmoBase\include"

rmdir /S /Q GizmoBase\libs\windows\x64
mklink /D GizmoBase\libs\windows\x64 "%CSW%\ws\vs17\CSW\x64"

rem ------------------------- Gizmo3D libs --------------------------------

rmdir /S /Q Gizmo3D\include
mklink /D Gizmo3D\include "%GIZMOSDK%\Gizmo3D\include"

rmdir /S /Q Gizmo3D\libs\windows\x64
mklink /D Gizmo3D\libs\windows\x64 "%CSW%\ws\vs17\CSW\x64"

rem ------------------------- Coordinate libs --------------------------------

rmdir /S /Q Coordinate\include
mklink /D Coordinate\include "%GIZMOSDK%\plugins\gzCoordinate\include"

rmdir /S /Q Coordinate\libs\windows\x64
mklink /D Coordinate\libs\windows\x64 "%CSW%\ws\vs17\CSW\x64"

rem ------------------------- CSW SceneManager libs --------------------------------

rmdir /S /Q SceneManager\include
mklink /D SceneManager\include "%CSW%\source\Presentation\Streaming\Map Streamer\cswSceneManager\include"

rmdir /S /Q SceneManager\libs\windows\x64
mklink /D SceneManager\libs\windows\x64 "%CSW%\ws\vs17\CSW\x64"