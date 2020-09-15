import cv2
import numpy as np
import os
import sys
import tensorflow as tf
import pickle
import datetime

from sklearn.model_selection import train_test_split

import matplotlib.pyplot as plt

EPOCHS = 10
IMG_WIDTH = 30
IMG_HEIGHT = 30
NUM_CATEGORIES = 43
TEST_SIZE = 0.3

def main():

    # Check command-line arguments
    if len(sys.argv) not in [2, 3]:
        sys.exit("Usage: python traffic.py data_directory [model.h5]")

    # Get image arrays and labels for all image files
    images, labels = load_data(sys.argv[1])

    # Split data into training and testing sets
    labels = tf.keras.utils.to_categorical(labels)
    x_train, x_test, y_train, y_test = train_test_split(
        np.array(images), np.array(labels), test_size=TEST_SIZE
    )

    # Get a compiled neural network
    model = get_model()

    # Fit model on training data
    history = model.fit(x_train, y_train, epochs=EPOCHS, validation_data=(x_test, y_test)) # create history object

    # Evaluate neural network performance
    model.evaluate(x_test,  y_test, verbose=2)

    plt.plot(history.history['accuracy'], label='Accuracy (testing data)')
    plt.plot(history.history['val_accuracy'], label='Accuracy (validation data)')
    plt.title('Accuracy')
    plt.ylabel('Accuracy value')
    plt.ylim(0, 1)
    plt.xlabel('No. epoch')
    plt.legend(loc="upper left")
    if len(sys.argv) == 3:
      plt.savefig(sys.argv[2]+".png")
    
    # Save model to file
    if len(sys.argv) == 3:
        filename = sys.argv[2]
        model.save(filename)
        print(f"Model saved to {filename}.")


def load_data(data_dir):
    """
    Load image data from directory `data_dir`.

    Assume `data_dir` has one directory named after each category, numbered
    0 through NUM_CATEGORIES - 1. Inside each category directory will be some
    number of image files.

    Return tuple `(images, labels)`. `images` should be a list of all
    of the images in the data directory, where each image is formatted as a
    numpy ndarray with dimensions IMG_WIDTH x IMG_HEIGHT x 3. `labels` should
    be a list of integer labels, representing the categories for each of the
    corresponding `images`.
    """
    
    '''
    images = []
    labels = []
    
    dircount = 1    
    
    for root, dirs, files in os.walk(data_dir, topdown=True): # iterate over labelled subdirectories
        for label in dirs:
            for filename in os.listdir(os.path.join(data_dir, label)): # iterate over files in each label's directory
                image_array = cv2.imread(os.path.join(data_dir, label, filename))
                image_array = cv2.resize(image_array,(IMG_WIDTH, IMG_HEIGHT), interpolation = cv2.INTER_CUBIC) # read and scale image
                labels.append(label)
                images.append(image_array)
                
            print("Loaded directory: " + str(dircount) + "/" + str(NUM_CATEGORIES) + " (Label: " + label + ")")
            dircount += 1
    
    # save this output to pickle to save a lot of time later.
    with open(str(NUM_CATEGORIES) + '-train.pickle', 'wb') as f:
        pickle.dump((images, labels), f)
    '''
    
        
    with open(str(NUM_CATEGORIES) + '-train.pickle', 'rb') as f:
           (images, labels) = pickle.load(f)
    
    
    return (images, labels)

def get_model():
    """
    Returns a compiled convolutional neural network model. Assume that the
    `input_shape` of the first layer is `(IMG_WIDTH, IMG_HEIGHT, 3)`.
    The output layer should have `NUM_CATEGORIES` units, one for each category.
    """
    
    model = tf.keras.Sequential([        
        tf.keras.layers.Conv2D(16, (3, 3), activation='relu', input_shape=(IMG_WIDTH, IMG_HEIGHT, 3)),
        tf.keras.layers.MaxPooling2D((2, 2)),
        tf.keras.layers.Conv2D(32, (3, 3), activation='relu'),
        tf.keras.layers.MaxPooling2D((2, 2)),
        tf.keras.layers.Conv2D(32, (3, 3), activation='relu'),
        tf.keras.layers.Flatten(),
        tf.keras.layers.Dense(16, activation='relu'),
        #tf.keras.layers.Dropout(0.2),
        tf.keras.layers.Dense(16, activation='relu'),
        #tf.keras.layers.Dropout(0.2),
        tf.keras.layers.Dense(NUM_CATEGORIES, activation='softmax')
    ])

    model.compile(optimizer=tf.keras.optimizers.Nadam(lr=0.002),
        loss='categorical_crossentropy',
        metrics=['accuracy'])

    return model


if __name__ == "__main__":
    main()
