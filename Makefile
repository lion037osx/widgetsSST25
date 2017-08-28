#app : xc32Sst25Flash
all:
	chmod -R 777 *
	chmod 777 *
help:
	@+echo ""
	@+echo ""
	@+echo "*********************************Help GIT******************************************"
	@+echo ""
	@+echo "make clone"
	@+echo "		git clone https://github.com/lion037osx/widgetsSST25.git"
	@+echo "make push"
	@+echo "		git push origin"
	@+echo "make pull"
	@+echo "		git pull origin"
	@+echo "make commit"
	@+echo "		git commit -m \"update\""
	@+echo "make add"
	@+echo "		git add ."
	@+echo "		git commit - m \"update\""
	@+echo "		git push origin master"
	@+echo "make fetch"
	@+echo "make update"
	@+echo "make upgrade"
	@+echo ""
	@+echo "		Copyrigth by Leo"
	@+echo ""
	@+echo ""
clone:
	git clone https://github.com/lion037osx/widgetsSST25.git
commit:
	git commit -m "update"
add:
	git add .
status:
	git status
	git remote -v
merge:
	git merge
	#git remote -v
upgrade:
	git add .
	git commit -m "update"
	git push origin master
update:
	git pull --all
fetch:
	git fetch origin
push:
#	git add.
#	git commit -m "update"
#	git push origin master 
#	git push https://github.com/lion037osx/widgetsSST25.git

	git push origin
pull:
#	git add .
#	git commit -m "upgrade"
#	git pull origin master
#	git pull git push https://github.com/lion037osx/widgetsSST25.git
	git pull origin
init:
	echo "# widgetsSST25" >> README.md
	git init
	git add README.md
	git commit -m "transfer bmp to Uc pi32"
	git remote add origin https://github.com/lion037osx/widgetsSST25.git
	git push -u origin master
