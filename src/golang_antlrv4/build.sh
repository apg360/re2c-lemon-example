# How to use with Go 1.16.1
# https://maelvls.dev/go111module-everywhere
# https://blog.golang.org/using-go-modules

# Tutorial source
# https://blog.gopheracademy.com/advent-2017/parsing-with-antlr4-and-go/
# https://github.com/antlr/antlr4/blob/master/doc/go-target.md


#STEP1
export parsername=parser
rm -rf $parsername
shopt -s expand_aliases 		# Aliases are not expanded when the shell is not interactive, unless the expand_aliases shell option is set using shopt
alias antlr='java -Xmx500M -jar $PWD/antlr-4.9.1-complete.jar'
antlr -Dlanguage=Go -o $parsername Calc.g4
cd parser && go mod init $parsername


#If one want to install in GO (like go get), it must go in GOROOT
#as root user do :
#unzip antlr.zip && cp antlr $(go env GOROOT)/src
#cp -R parser $(go env GOROOT)/src
#cd $(go env GOROOT)/src
#go build antlr
#go build parser
