#include <stdio.h>
#include <stdlib.h>

// 데이터를 저장할 구조체 정의
typedef struct {
    char key[20];
    int values[3];
} Data;

int main() {
    // 파일 경로
    const char *file_path = "marbleBoardConfig.txt";  // 파일 경로를 실제 파일의 경로로 바꿔주세요.

    // 파일 열기
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "파일을 열 수 없습니다.\n");
        return 1;
    }

    // 데이터를 저장할 배열 동적 할당
    Data *data_array = (Data*)malloc(sizeof(Data) * 16);  // 예제 데이터가 16개이므로 크기를 조절
    if (data_array == NULL) {
        fprintf(stderr, "메모리를 할당할 수 없습니다.\n");
        fclose(file);
        return 1;
    }

    int index = 0;
    char line[100];  // 각 줄을 읽어올 버퍼

    // 파일에서 각 줄을 읽어와 데이터 구조화
    while (fgets(line, sizeof(line), file) != NULL && index < 16) {
        sscanf(line, "%s %d %d %d", data_array[index].key, &data_array[index].values[0], &data_array[index].values[1], &data_array[index].values[2]);
        index++;
    }

    // 파일 닫기
    fclose(file);
	int temp ;
	
    // 결과 출력
    for (int i = 0; i < index; i++) {
        printf("%s: %d %d %d\n", data_array[i].key, data_array[i].values[0], data_array[i].values[1], data_array[i].values[2]);
        if(data_array[i].values[0]==3) temp = data_array[i].values[2];
    }

    // 동적 할당된 메모리 해제
    free(data_array);
	
	printf("%d", temp);
    return 0;
}

