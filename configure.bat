@echo off
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::
:: Copyright (C) 2020 The Qt Company Ltd.
:: Contact: http://www.qt.io/licensing/
::
:: This file is part of the tools applications of the Qt Toolkit.
::
:: $QT_BEGIN_LICENSE:GPL-EXCEPT$
:: Commercial License Usage
:: Licensees holding valid commercial Qt licenses may use this file in
:: accordance with the commercial license agreement provided with the
:: Software or, alternatively, in accordance with the terms contained in
:: a written agreement between you and The Qt Company. For licensing terms
:: and conditions see https://www.qt.io/terms-conditions. For further
:: information use the contact form at https://www.qt.io/contact-us.
::
:: GNU General Public License Usage
:: Alternatively, this file may be used under the terms of the GNU
:: General Public License version 3 as published by the Free Software
:: Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
:: included in the packaging of this file. Please review the following
:: information to ensure the GNU General Public License requirements will
:: be met: https://www.gnu.org/licenses/gpl-3.0.html.
::
:: $QT_END_LICENSE$
::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

: get current path
set "srcpath=%~dp0"

: get crrent scrite file path
set path=%cd%
echo %path%

set "configure=%srcpath%qtbase\configure.bat"

: make sure file [.\qtbase\configure.bat] is exit.
if not exist "%configure%" (
    echo %configure% not found. Did you forget to run "init-repository"? >&2
    exit /b 1
)

if not exist qtbase mkdir qtbase || exit /b 1

echo + cd qtbase
cd qtbase || exit /b 1

: %* is all args from command, pass to  .\qtbase\configure.bat
: then call .\qtbase\configure.bat -top-level %*

echo + %configure% -top-level %*
call %configure% -top-level %*
set err=%errorlevel%

cd ..

exit /b %err%
