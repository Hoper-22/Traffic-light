# Traffic-light

 https://youtu.be/Jd43T0fPnak

 ![KakaoTalk_20250316_152850873](https://github.com/user-attachments/assets/01772c28-0efe-4953-8fe2-7a9f124541ad)


![image](https://github.com/user-attachments/assets/4e38ccae-3a9b-4e5a-b5e9-cc711edb8c05)

빨간색, 노란색, 초록색 LED가 차례대로 13번, 12번, 11번 포트에 연결되어있고, 세개의 버튼이 각각 순서대로 4, 3, 2번 포트에 연결했다. 그 후 회로가 연결이 될 수 있도록 각각의 (-) 부분을 밑으로 연결하고, GND 와 (-) 부분이 연결이 될 수 있도록 회로를 구성했다.

![image](https://github.com/user-attachments/assets/9302f27e-ed9e-406c-b579-001473d87320)

각각의 라이브러리를 포함시킨 뒤, LED와 버튼을 각각 연결한 핀에 맞는 번호를 할당시켜주고, 세개의 버튼의 상태를 false 로 초기값을 설정해준다. 
이후에 쓰일 깜빡임 카운트 또한 0으로 초기값을 설정해준다.
TaskScheduler 객체를 생성해준다.

![image](https://github.com/user-attachments/assets/75be97cb-5338-45a5-a47a-fe86766f4c80)

Task 를 다음과 같이 구간별로 나누어 만들기 위해 미리 구간을 선언해준다.

![image](https://github.com/user-attachments/assets/ff41402b-be0e-4574-86a5-e295632e803d)

무한 반복될 객체를 선언해준다.
이후 Task를 시작해주는 함수를 생성한다.

![image](https://github.com/user-attachments/assets/9b873d84-6499-4f63-ae59-1a8ce678ab7f)

버튼을 누르면 하던 일을 즉시 멈추고 해당되는 일을 실행하게 해주는 함수를 작성해준다. 
버튼을 떼면 다시 루프를 돌 수 있게끔 코드를 작성하는 것을 잊지 않고 작성해준다.

![image](https://github.com/user-attachments/assets/a7d566a8-c3ca-4c77-b64a-f5db23181e90)

LED와 버튼의 핀 모드를 설정해준다.
이후 버튼이 눌렸을 때의 인터럽트를 설정해준다.
Task 객체들을 TaskScheduler 에 추가시켜준다.
이후 TrafficOn 함수를 실행시켜 Task 를 시작한다.

![image](https://github.com/user-attachments/assets/e62b2e83-91dd-460c-9ad5-94dbaf0aa797)

Task1 에서는 깜빡임 카운트를 0으로 재설정 및 초기화, 이후에 나올 Task6에서 켜진 노란색 LED를 꺼주고, 빨간색 LED를 킨 채 다음 Task까지 2초를 기다리게끔 해준다.
Task2 에서는 켜져있는 빨간색 LED를 즉시 끄고, 노란색 LED를 킨 채 다음 Task까지 0.5초를 기다리게끔 해준다.
Task3 에서는 켜져있는 노란색 LED를 즉시 끄고, 초록색 LED를 킨 채 다음 Task까지 2초를 기다리게끔 해준다.

![image](https://github.com/user-attachments/assets/b585edaf-2c50-499f-aa4e-d11213245367)
![Task_4-6](https://github.com/user-attachments/assets/48ee1918-4e41-46dc-a2e6-2721c567d1c4)

다음과 같이 Task 4 와 5 를 3번 반복시켜 깜빡여준 뒤, Task 6에서 초록색 LED를 끄고, 노란색 LED를 킨 채 Task1 까지 2초를 기다리게끔 해준다.

전체적인 Task 는 다음과 같다.

![Task](https://github.com/user-attachments/assets/04de30c9-1046-4f2f-8a8c-845eaefd1d13)

![image](https://github.com/user-attachments/assets/a2575836-468e-4f42-bd05-3411721567dc)

인터럽트를 활성화하기 위해
1. 만약 첫번째 버튼이 눌리면 빨간색 불만 켜져있게 한다.
2. 만약 두번째 버튼이 눌리면 모든 불이 0.2초 간격으로 꺼졌다 켜졌다 반복한다.
3. 만약 세번째 버튼이 눌리면 모든 불이 꺼진다.
4. 모두 아니라면 루프를 계속해 실행한다.

이 과정을 loop 에 넣어 실시간으로 감시하게끔 해준다.
