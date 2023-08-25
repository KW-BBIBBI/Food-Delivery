<GIT>
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

git pull origin master --allow-unrelated-histories
-- 깃이랑 웹이랑 달라서 푸쉬할때 풀하고 푸쉬해야함

git레포지토리 추가 후 커밋하기
> (local) git btanch -M main 으로 local branch name 변경 (server default name: main)
> (local) git remote add orogin (URL)
> (local) git push origin main

git branch관리
> (local) git branch (new branch) # branch생성
> (local) git checkout (branch name) # branch 이동
> (local) git merge (merge할 branch name) # 현재 branch에 merge 시킴

원본 프로젝트 저장소를 원격 저장소로 추가
git remote add (aliasname) (link)


원격 저장소 설정 현황 확인방법
$ git remote -v

