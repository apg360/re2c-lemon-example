module myexample_golang_antlrv4

require "github.com/antlr/antlr4/runtime/Go/antlr" v0.0.0
replace "github.com/antlr/antlr4/runtime/Go/antlr" v0.0.0 => "./antlr_4.9.1_go_runtime"

require "parser" v0.0.0
replace "parser" v0.0.0 => "./parser"

go 1.16
