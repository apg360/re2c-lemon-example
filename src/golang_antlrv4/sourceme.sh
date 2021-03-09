#https://github.com/antlr/antlr4/blob/master/doc/go-target.md
#go get -u -insecure github.com/antlr/antlr4/runtime/Go/antlr

alias antlr='java -Xmx500M -jar $PWD/antlr-4.9.1-complete.jar'
#source sourceme.sh
#antlr -Dlanguage=Go -o parser Calc.g4
# https://blog.gopheracademy.com/advent-2017/parsing-with-antlr4-and-go/


# Go get Manual install
#go env
#export GOPATH=$(go env GOPATH)
#cd $GOPATH
#mkdir -p github.com/antlr/antlr4/runtime/Go/antlr
#cd $GOPATH/github.com/antlr/antlr4/runtime/Go/antlr
#git clone github.com/antlr/antlr4/runtime/Go/antlr
#go mod init github.com/antlr/antlr4/runtime/Go/antlr
#go build

