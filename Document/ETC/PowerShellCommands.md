# Power Shell 명령어 모음

**Windows 패키지 매니저(Chocolatey)**

Installation

> Set-ExecutionPolicy Bypass -Scope Process -Force; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))

Searching for package

> choco search git

installing package

> choco install googlechrome -y

- [출처: installing-chocolatey-package-manager-on-windows](http://54.184.76.36/installing-chocolatey-package-manager-on-windows/)

**환경 변수 생성 및 할당**

$env:<envrionment variable name> = '<environment variable value>'

> $env:AZURE_RESOURCE_GROUP = 'MyTestResourceGroup'

**환경 변수 리스트업**

> dir env:

- [출처 : tutorialspoint](https://www.tutorialspoint.com/how-to-set-environment-variables-using-powershell?msclkid=7385124bcf8e11ecadb4331475d6bd4a)