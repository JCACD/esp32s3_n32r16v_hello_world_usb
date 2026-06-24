#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_random.h"

void app_main(void)
{
    const char *bars[] = {
        "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"
    };

    int level[16];

    printf("Starting animation... Press [ESC] key to stop.\n");
    vTaskDelay(pdMS_TO_TICKS(500));

    while (1) {
        // 非阻塞讀取輸入：USB Serial JTAG 綁定 console → 用 fgetc(stdin)
        int ch = fgetc(stdin);
        if (ch == 27) { // ESC = 27
            printf("\n\033[2K\rESC pressed. Animation stopped.\n");
            break;
        }

        // 產生隨機高度
        for (int i = 0; i < 16; i++) {
            level[i] = esp_random() % 8;
        }

        // 顯示動畫
        printf("\033[2K\r");
        for (int i = 0; i < 16; i++) {
            printf("%s ", bars[level[i]]);
        }
        fflush(stdout);

        vTaskDelay(pdMS_TO_TICKS(120)); // 控制幀率
    }

    printf("Program finished.\n");
}
