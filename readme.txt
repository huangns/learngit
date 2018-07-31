/********* 0 introduction **********/
Git is a distributed version control system.
Git is free software distributed under the GPL.
Git has a mutable index called stage.
1. mkdir xxx
2.cd xxx
3.git init, ls -a, there is .git file.
4.edit txt file, not image, video, word.

5.git add xx.txt
  git add xxx.txt
  ...git can add many files before commit.
6 git commit -m "add x files." //-m " *** " to tell user what have be done.

/***************2*******************/
1.git status
//to know the changes on current repository. if there are some file changed, we will see "changes not staged for commit".
2.git diff:
 to see the difference between two files before change and after change.

 /*************3************/
 git log: record commit history
 git log --pretty=oneline

git reset --hard HEAD^
git reset --hard HEAD^^
git reset --hard HEAD~100
 
git reflog //record all operation, including commit, reset ..
so we can know all commit id.

git reset --hard xxxxx  //reset through commit id.

HEAD pointer: point to current version.
/*
HEAD指向的版本就是当前版本，因此，Git允许我们在版本的历史之间穿梭，使用命令git reset --hard commit_id。
穿梭前，用git log可以查看提交历史，以便确定要回退到哪个版本。
要重返未来，用git reflog查看命令历史，以便确定要回到未来的哪个版本。
*/

/******work directory, stage, master ***********/
1.working directory: learngit
2.stage: git add , file to stage
3.master: is a branch, HEAD pointer point to.
工作区有一个隐藏目录.git，这个不算工作区，而是Git的版本库。
Git的版本库里存了很多东西，其中最重要的就是称为stage（或者叫index）的暂存区，还有Git为我们自动创建的第一个分支master，以及指向master的一个指针叫HEAD。


git diff HEAD -- readme.txt
git diff HEAD^ -- readme.txt


