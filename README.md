# Robot Controller

This is an Robot Controller project using NodeJS, Firebase, ESP8266, Arduino Mega to control robot aim 3dof

## Deploy Heroku using Docker

`docker build . -t khanhnq1406/robot-controller`

`heroku container:login`

`heroku container:push web --app robot-controller-hcmute`

`heroku container:release web --app robot-controller-hcmute`
