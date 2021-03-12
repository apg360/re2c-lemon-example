# How to use with Go 1.16.1
# https://maelvls.dev/go111module-everywhere
# https://blog.golang.org/using-go-modules

# Tutorial source
# https://blog.gopheracademy.com/advent-2017/parsing-with-antlr4-and-go/
# https://github.com/antlr/antlr4/blob/master/doc/go-target.md


#STEP1
alias antlr='java -Xmx500M -jar $PWD/antlr-4.9.1-complete.jar'
antlr -Dlanguage=Go -o parser Calc.g4

#STEP2 as root user
unzip antlr.zip && cp antlr /usr/lib/go/src
cp -R parser /usr/lib/go/src
cd /usr/lib/go/src
go build antlr
go build parser





################################# TO DELETE
# If no internet, then to do "go get" Manually
#go env
#export GOPATH=$(go env GOPATH)
#cd $GOPATH
#mkdir -p src/github.com/antlr/antlr4
#cd $GOPATH/src/github.com/antlr/antlr4
#git clone github.com/antlr/antlr4 (or unzip the zip file)
#go test
#go mod init
#go mod tidy
#go build github.com/antlr/antlr4/runtime/Go/antlr
#go install github.com/antlr/antlr4/runtime/Go/antlr

