# Prompt

export PS1=$'%n@%m %~$ '
#export PS1=$'\e[0;34m%n\e[0m@\e[0;37m%m \e[1;96m%~\e[0m$'
#export PS1=$PS1' '
export FTPROJECT='ft_printf'
export MAXINT=2147483647
export INT=$MAXINT

# Aliases

alias zp="source ~/.zprofile"
alias ze="vim ~/.zprofile"
alias nr="norminette -R CheckForbiddenSourceHeader"
alias gccw="gcc -Wall -Wextra -Werror"
alias cdc="cd && clear"
alias maxint="printf $MAXINT | pbcopy"
alias code="/Applications/Visual\ Studio\ Code.app/Contents/Resources/app/bin/code"
alias l="leaks --atExit -- "
alias lk="leaks --atExit -- "
alias lks="leaks --atExit -- "
alias lsl='ls -lah'
alias ga='git add'
alias gc='git commit -m'
alias gp='git push'
alias mkcpp='cp ~/.Makefile ./Makefile && mkdir include && mkdir src'

#inception aliases
alias issh='ssh -l rleskine -p 3022 localhost'
alias icd='cd /Volumes/KINGSTON'
alias ibak='cp /Volumes/KINGSTON/inception_dev/inception_dev.vdi /Volumes/KINGSTON/inception_dev_backup.vdi'

#componysorvor no touchy
alias cssh='ssh -l rleskine filesforsats.com'

tabn() { echo -ne "\e]1;$@\a"; }
ex() { if [ ! -d "ex00" ]; then cd ..; fi; cd ex0$@; }
cdp() { if [ "$#" -gt 0 ]; then cd "$HOME/$FTPROJECT/$@"; else cd "$HOME/$FTPROJECT"; fi }
cpp() { if [ "$#" -gt 0 ]; then cd "$HOME/cppmodules/cpp0$1"; else cd "$HOME/cppmodules"; fi; if [ "$#" -eq 2  ]; then cd "ex0$2"; fi }
c++() { if [ "$#" -gt 0 ]; then cd "$HOME/c++modrepo/cpp0$@"; else cd "$HOME/c++modrepo"; fi }
clex() { echo "Making fclean in ex folders"; for i in $(seq 0 9); do if [ -d "ex0$i" ]; then make -C ex0$i fclean; fi; done }
exmk() { echo "Making $@ in ex folders"; for i in $(seq 0 9); do if [ -d "ex0$i" ]; then make -C ex0$i $@; fi; done }
mkex() { 
	if [ "$#" -eq 0 ]; then 
		echo "Copying Makefile and creating include/src folders";
		cp ~/.Makefile ./Makefile
	    mkdir src include
	elif; then 
		echo "Creating $@ directory";
		mkdir $@;
		cd $@;
		newex;
	fi;
}
testparnbr() { echo "$#" }

# Tab names and colors

case  ${ITERM_SESSION_ID:3:1} in
	0)
		echo -ne "\e]1;one\a"
		echo -e "\033]6;1;bg;red;brightness;181\a"
		echo -e "\033]6;1;bg;green;brightness;215\a"
		echo -e "\033]6;1;bg;blue;brightness;73\a"
		;;
	1)
		echo -ne "\e]1;two\a"
		echo -e "\033]6;1;bg;red;brightness;240\a"
		echo -e "\033]6;1;bg;green;brightness;220\a"
		echo -e "\033]6;1;bg;blue;brightness;79\a"
		;;
	2)
		echo -ne "\e]1;three\a"
		echo -e "\033]6;1;bg;red;brightness;251\a"
		echo -e "\033]6;1;bg;green;brightness;107\a"
		echo -e "\033]6;1;bg;blue;brightness;98\a"
		;;
	3)
		echo -ne "\e]1;four\a"
		echo -e "\033]6;1;bg;red;brightness;120\a"
		echo -e "\033]6;1;bg;green;brightness;120\a"
		echo -e "\033]6;1;bg;blue;brightness;120\a"
		;;
	4)
		echo -ne "\e]1;five\a"
        	echo -e "\033]6;1;bg;red;brightness;110\a"
	        echo -e "\033]6;1;bg;green;brightness;110\a"
	        echo -e "\033]6;1;bg;blue;brightness;200\a"
		;;
esac

# faster animation (doesnt seem to work)
defaults write com.apple.dock workspaces-edge-delay -float 0.1

# Unused
#alias d07="cd ~/d07/0"#alias d08="cd ~/d08/0"#alias d09="cd ~/d09/0"#alias d10="cd ~/d10/0"#alias d11="cd ~/d11/0"#alias d12="cd ~/d12/0"#alias d13="cd ~/d13/0"#alias bsq="cd ~/bsq/0/alpha"
#defaults write -g com.apple.swipescrolldirection -bool FALSE
#	echo -ne \"\e]1;"%1"\a\"

# osascript ~/misc/openmousemenu.scpt
