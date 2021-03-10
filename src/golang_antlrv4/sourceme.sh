#https://github.com/antlr/antlr4/blob/master/doc/go-target.md
#go get -v -u github.com/antlr/antlr4/runtime/Go/antlr

alias antlr='java -Xmx500M -jar $PWD/antlr-4.9.1-complete.jar'
#source sourceme.sh
#antlr -Dlanguage=Go -o parser Calc.g4
# https://blog.gopheracademy.com/advent-2017/parsing-with-antlr4-and-go/


# If no internet, then to do "go get" Manually
#go env
#export GOPATH=$(go env GOPATH)
#cd $GOPATH
#mkdir -p src/github.com/antlr/antlr4
#cd $GOPATH/github.com/antlr/antlr4
#git clone github.com/antlr/antlr4 (or unzip the zip file)
#go mod init github.com/antlr/antlr4/runtime/Go/antlr
#go build
#go install
