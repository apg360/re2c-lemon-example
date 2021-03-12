# How to use with Go 1.16.1
# https://maelvls.dev/go111module-everywhere
# https://blog.golang.org/using-go-modules

# Tutorial source
# https://blog.gopheracademy.com/advent-2017/parsing-with-antlr4-and-go/
# https://github.com/antlr/antlr4/blob/master/doc/go-target.md


#STEP1
alias antlr='java -Xmx500M -jar $PWD/antlr-4.9.1-complete.jar'
antlr -Dlanguage=Go -o parser Calc.g4



#If one want to install in GO (like go get), it must go in GOROOT
#as root user do :
#unzip antlr.zip && cp antlr $(go env GOROOT)/src
#cp -R parser $(go env GOROOT)/src
#cd $(go env GOROOT)/src
#go build antlr
#go build parser
