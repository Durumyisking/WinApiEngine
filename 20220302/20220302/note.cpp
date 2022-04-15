#include "pch.h"





/*

	r * 3.14 = 둘레의 절반

	라디안 : 반지름과 호의 길이와의 실질적인 비율값

	우리는 파이를 각도로 볼거임

	3.14 라디안 = 180도

	라디안이 1일때 호의 길이 = 반지름



	cos = 밑변 / 빗변으로, 빗변이 1일때 밑변이 어느정도인지 비율
	나머지는 그대로

	cos0 = 1	cos90 = 0	cos180 = -1 
	sin0 = 0	sin90 = 1	sin180 = 0


	우리가 직선으로 100을 가려면 1프레임마다 100 * DT씩 이동해서 100에 도달 이때 1초 걸림
	우리가 45도 방향으로 100을 가고싶다 칠때 45도 방향으로 100을 그은 후 그때 좌표의 x, y를 구해서 피타고라스 정리로 구해얗마
	그때의 x는 100cos45		y는 100sin45
	d

*/
	


/*
	project 흐름

	***obj delete***
	1frame
	update		: 
	finalupdate	: 2. oncollision enter
	collision	: 1. 콜리전 발생
	render		: 4. obj set dead, 5. deadvec.pushback(obj)
	event		: 3. Delete event

	2frame
	update		: 
	finalupdate	: 
	collision	: 
	render		: 6. dead상태인 obj scene내에서 erase
	event		: 7. 등록해놓은 deadvec 비우기

*/


/*

	Scene 이 바뀔때
	A scene에 있
	change scene 과정에서 다음 scene에 넘기겠다고 마킹해둔것들만 따로 모아서 
	다음 scene의 enter에 넣어주면 유지된체로 넘겨줄 수 있음

*/

/*
	Unity Build
	평소에는 우리가 클래스들을 나누어서 코딩을 했지만
	빌드할때만 하나의 Cpp에 모아서 빌드한다

	모든 클래스를 빌드에서 제외시키고
	임시 cpp file을 생성 
	그 cpp file에
	include cpp

	방법 : 프로젝트 vcsproj 파일을 메모장으로 연 후
	  <PropertyGroup>
	<EnableUnitySupport>true</EnableUnitySupport>
  </PropertyGroup>
  이거 넣고 비주얼 껐다 킨 다음
  프로젝트 속성 - c/cpp - unitybuild
  unity 파일 디렉터리 $(ProjectDir)\폴더명\
  unity 파일의 최소 소스 수 8
  
  다중 프로세서 컴파일 = yes
  미리컴파일된 헤더 -> 사용
  
	
*/

/*
	기존의 다른 창을 사용하지 못한다 (프로그램의 제어권 독점함)
	ex) 에러 메시지를 생각해보면 에러가뜨면 확인또는 취소를 눌라야만 다음으로 진행이가능
	그동안 뒤에있는 창은 선택이 불가

*/