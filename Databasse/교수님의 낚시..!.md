## 설치방법
#### 학교 컴퓨터 기준으로 설정된 환경
#### 개인 컴퓨터는 조금 다를 수 있다.

1. https://www.oracle.com/technetwork/database/enterprise-edition/downloads/index.html 접속
2. Oracle Database 12c Release 1 - 운영 체제 맞춰서 설치
3. setup 더블 클릭 후, 모든 체크 해제한 뒤
4. 기본적인 설정대로 다음 클릭
5. 새 Windows 사용자 생성 </hr>
    - ID : hongik, PW : password
6. 기본 설치 -> 다른 내용은 그대로 하고, PW : Password1234$
7. 설~치~중~
8. 근데, 이거 뻘짓.. 교수님이 뻘짓 시킴.. windows10에서 설치 잘 안된다.

## sql plus : command 기반 sql tool

## 교재 저자 사이트
#### http://pages.cs.wisc.edu/~dbbook/openAccess/thirdEdition/supporting_material.htm
#### sql plus에서 사이트에 있는 스크립트를 실행하는 방법 </hr>
    - <b> Material for Students and Instructors </b> 에서 하단의 SQL script to create the tables for the exercise &  Exercise 5.1, 2, 3, 4, 5에서 예시 스크립트를 다운로드
    - start sql 파일경로
    - 

## Database 삭제하는 방법 </hr>
    - 1. services.msc 에서 모든 oracle 이름으로 시작하는것 중지
    - 2. regedit -> HKEY_LOCAL_MACHINE , SW.system 에서 
    - 3. C:\app\hongik 모두 삭제
       + Lock Hunter에서 뭐가 삭제를 락하는지 확인 가능
    - 4. C:\ProgramFiles\oracle 모두 삭제
    - 5. C:\Temp 모두 삭제 
