#/bin/bash!
alias ctags="`brew --prefix`/bin/ctags"
alias ctags >> ~/.bash_profile
ctags --recurse=yes --exclude=.git
