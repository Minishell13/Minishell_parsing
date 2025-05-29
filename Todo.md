## Lexer
## Parser

> <<kdsjf && (ls <<in1 arg1 >>out1) >ls && ls
COMPLETE_COMMAND
  AND
    IO_REDIRECT
      HEREDOC: "kdsjf" , 1
    SUBSHELL
      SIMPLE_COMMAND: [ ls ,  arg1 ]
        IO_REDIRECT
          HEREDOC: "in1" , 1
          REDIR_APPEND: "out1" , 0
  AND
    IO_REDIRECT
      REDIR_OUT: "ls" , 0
    SIMPLE_COMMAND: [ ls ]



(asdasd --> leak
