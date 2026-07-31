#include "Task_TinyML.h"

constexpr int kTensorArenaSize = 8 * 1024;
uint8_t tensor_arena[kTensorArenaSize];

const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input_tensor = nullptr;
TfLiteTensor* output_tensor = nullptr;

float inference = 0.0;

void TaskTinyML(void*) {
    SetUpTinyML();

    while (1) {
        float current_temp = temperature[read_pointer];
        float current_humidity = humid[read_pointer];

        input_tensor->data.f[0] = current_temp;
        input_tensor->data.f[1] = current_humidity;

        TfLiteStatus invoke_status = interpreter->Invoke();

        if (invoke_status == kTfLiteOk) {
            inference = output_tensor->data.f[0];

            Serial.printf(" Inference: %f", inference);
        }
        else {
            Serial.println(" [Edge AI Task] Error running model inference!");
        }

        vTaskDelay(1000);
    }
}

void SetUpTinyML() {

    model = tflite::GetModel(g_model);

    static tflite::AllOpsResolver resolver;
    static tflite::MicroErrorReporter error_reporter;

    static tflite::MicroInterpreter static_interpreter(
        model, 
        resolver, 
        tensor_arena, 
        kTensorArenaSize, 
        &error_reporter
    );

    interpreter = &static_interpreter;


    interpreter->AllocateTensors();

    input_tensor = interpreter->input(0);
    output_tensor = interpreter->output(0);
}