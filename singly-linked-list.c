/* singly-linked-list.c
 *  단일 연결 리스트
 *
 * 자료구조 6번째 과제
 * 충북대학교 2017015040 물리학과 강수
 */


#include<stdio.h>
#include<stdlib.h>

//노드 구조체 정의
typedef struct Node {
	int key;
	struct Node* link;
} listNode;

//첫 번째 노드를 가르키는 구조체
typedef struct Head {
	struct Node* first;
} headNode;

//함수선언
headNode* initialize(headNode* h);// 초기화 함수
int freeList(headNode* h);//메모리 해제 함수

int insertFirst(headNode* h, int key);//처음에 노드 추가
int insertNode(headNode* h, int key);//숫자 크기를 비교해서 알맞은 위치에 노드 추가
int insertLast(headNode* h, int key);//마지막에 노드 추가

int deleteFirst(headNode* h);//처음 노드를 삭제
int deleteNode(headNode* h, int key);//해당 값과 같은 노드 하나를 삭제
int deleteLast(headNode* h);//마지막 노드를 삭제
int invertList(headNode* h);//리스트 역순으로 만드는 함수

void printList(headNode* h);//노드 내용 출력 함수

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;//노드 시작주소
		printf("[-------------------- [kang su] [2017015040] -------------------]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {//노드 초기화 함수

	//headNode가 null이 아니면 할당했던 노드 전부 메모리 동적 할당 해제
	if(h != NULL)
		freeList(h);

	
	headNode* temp = (headNode*)malloc(sizeof(headNode));//malloc을 이용한 동적할당
	temp->first = NULL;//해드노드의 시작주소(first)의 값을 NULL로 초기화
	return temp;//동적 할당 시작 주소를 리턴
}

int freeList(headNode* h){//노드 메모리 전부 할당 해제
	
	listNode* p = h->first;//초기노드

	listNode* prev = NULL;//가르키는 노드 이전노드
	while(p != NULL) {//노드끝까지
		prev = p;//이전 노드 등록
		p = p->link;//다음노드를 가르킴
		free(prev);//이전 노드 해제
	}
	free(h);//초기 위치를 가르키는 노드도 해제
	return 0;
}


int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));//노드생성
	node->key = key;//노드에 입력한 값을 저장한다

	node->link=h->first;//새첫노드가 first가 가르키는 노드를 가르키게 한다
	h->first=node;//처음 노드 위치를 표기

	return 0;
}

//크기를 비교해서 노드추가
int insertNode(headNode* h, int key) {


	if(h->first==NULL){//노드가 없을경우
		insertFirst(h,key);//처음노드에 추가
		return 0;// 종료
	}
	//이미 노드가 있을 경우
	listNode* node = (listNode*)malloc(sizeof(listNode));//노드생성
	node->key = key;//노드에 값저장

	listNode* n = h->first;//처음노드 부터시작
	listNode* bn =n;//이전 노드를 가르키기 위한 변수
	if((n->key<node->key)){//처음노드와 비교해서 클경우
		//특정 노드 이후에 추가
		while(n != NULL&&(n->key<node->key)) {//비교해서 작지 않은 노드까지 이동
			bn =n;//전 노드를 기억한다
			n = n->link;//다음 노드로 주소변경
		}
		bn->link=node;//비교해서 작았던 노드가 node를 가르키도록
		node->link=n;//node가 비교해서 작지 않았던 노드를 가르키도록 한다.


			
	}else{//처음 노드 보다 작을경우 모든 노드이전에 추가
		insertFirst(h,key);//처음노드에 추가
		return 0;//종료
	}

	

	return 0;
}


//마지막에 노드추가
int insertLast(headNode* h, int key) {
	
	if(h->first==NULL){//노드가 없을경우
		insertFirst(h,key);//처음노드에 추가
		return 0;//가르킬 노드가 없으므로 종료
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));//노드생성
	node->key = key;//노드에 값저장
	node->link=NULL;//마지막 노드 임으로 마지막 노드로 설정
	
	listNode* n = h->first;//처음노드 부터시작
	while(n->link != NULL) {//마지막 노드까지 이동
		n = n->link;//다음 노드로 주소변경
	}
	n->link=node;//마지막 노드에 링크 값을 노드 위치로 설정
	return 0;
}


//처음 노드 지우기
int deleteFirst(headNode* h) {

	if(h->first==NULL){//노드가 없을경우
		return 0;// 종료
	}
	listNode* p = h->first;//삭제할 노드
	h->first=p->link;//삭제 한 노드 다음 노드로 연결
	free(p);//마지막 노드 해제
	return 0;
}


//해당 값과 같은 노드지우기
int deleteNode(headNode* h, int key) {

	if(h->first==NULL){//노드가 없을경우
		return 0;// 종료
	}
	listNode* p = h->first;//첫번째 노드등록

	listNode* prev = NULL;//해당 노드 전을 가르킬 포인터
	while(p->link != NULL&&p->key!=key) {//노드안 입력 값과 같은 노드는 해당 노드는 p가 된다. 
		prev = p;//해당 노드전
		p = p->link;//해당 노드or마지막 노드
	}
	if(p->key==key){//노드 안에 해당 값이 있을 경우
		if(prev!=NULL){//p이전 노드가 존재 할 경우
			prev->link=p->link;//해당 노드이후 노드와 연결
		}else{//해당 노드가 처음 노드인 경우	
			h->first=p->link;//삭제 한 노드 다음 노드로 연결
		}
		free(p);//해당 노드 해제
	}

	return 0;

}

//마지막 노드 지우기
int deleteLast(headNode* h) {
	
	if(h->first==NULL){//노드가 없을경우
		return 0;// 종료
	}
	listNode* p = h->first;//첫번째 노드등록

	listNode* prev = NULL;//마지막 노드 전을 가르킬 포인터
	while(p->link != NULL) {//마지막 노드는 p가 된다. 
		prev = p;//마지막 노드전
		p = p->link;//마지막 노드
	}

	free(p);//마지막 노드 해제
	if(prev!=NULL)//p이전 노드가 존재 할 경우
		prev->link=NULL;//마지막 노드로 선언

	return 0;
}


//리스트 뒤집기
int invertList(headNode* h) {
	if(h->first==NULL){//노드가 없을경우
		return 0;// 종료
	}
	listNode* p = h->first;//첫번째 노드등록
	if(p->link==NULL){//노드가 없을경우
		return 0;// 종료
	}
	listNode* prev = NULL;//p노드 전을 가르킬 포인터
	listNode* pLink = p->link;//다음 노드를 가르킬 포인터
	p->link=NULL;//처음노드를 마지막을 가르키도록 설정
	while(pLink != NULL) {//마지막 노드 까지 반복
		prev=p;//이전 노드등록
		p = pLink;//다음 노드로 이동
		pLink = p->link;//값을 바꾸기전 다음 노드위치를 기록
		p->link=prev;//지금 노드의 방향을 이전노드로
	}
	h->first=p;//마지막 노드를 처음으로 설정

	
	return 0;
}

//출력
void printList(headNode* h) {
	int i = 0;//노드 번호
	listNode* p;//노드

	printf("\n---PRINT\n");

	if(h == NULL||h->first == NULL) {//출력할게 없는경우
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;//처음노드

	while(p != NULL) {//처음부터 마지막 노드까지 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
