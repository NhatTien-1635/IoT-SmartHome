# AI code

import numpy as np
import tensorflow as tf

# 1. Create Training Data: [Temperature (°C), Humidity (%)] -> Target Fan Duty Cycle (0.0 to 1.0)
X = np.array([
    [18.0, 35.0], [20.0, 40.0], [22.0, 50.0],  # Cool/Dry -> Fan Low/OFF
    [25.0, 55.0], [28.0, 60.0], [30.0, 70.0],  # Warm -> Moderate Fan
    [32.0, 75.0], [35.0, 80.0], [38.0, 85.0]   # Hot/Humid -> High Fan
], dtype=np.float32)

y = np.array([
    [0.0], [0.0], [0.2],
    [0.4], [0.6], [0.8],
    [0.9], [1.0], [1.0]
], dtype=np.float32)

# 2. Build a Lightweight Sequential Neural Network
model = tf.keras.Sequential([
    tf.keras.layers.Dense(8, activation='relu', input_shape=(2,)),
    tf.keras.layers.Dense(1, activation='sigmoid') # Output scaled between 0.0 and 1.0
])

model.compile(optimizer='adam', loss='mse')
model.fit(X, y, epochs=300, verbose=0)

# 3. Convert Keras Model to TensorFlow Lite
converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

# 4. Convert Binary Bytes into C++ Header File (g_model.h)
def export_to_c_header(bytes_data, filename="g_model.h", var_name="g_model"):
    hex_bytes = [f"0x{b:02x}" for b in bytes_data]
    
    with open(filename, "w") as f:
        f.write("#ifndef G_MODEL_H_\n#define G_MODEL_H_\n\n")
        f.write("#include <cstdint>\n\n")
        f.write(f"alignas(16) const unsigned char {var_name}[] = {{\n  ")
        
        # Format 12 hex values per line
        for i in range(0, len(hex_bytes), 12):
            f.write(", ".join(hex_bytes[i:i+12]))
            if i + 12 < len(hex_bytes):
                f.write(",\n  ")
            else:
                f.write("\n")
                
        f.write("};\n\n")
        f.write(f"const unsigned int {var_name}_len = {len(bytes_data)};\n\n")
        f.write("#endif  // G_MODEL_H_\n")

export_to_c_header(tflite_model)
print("Successfully generated g_model.h!")