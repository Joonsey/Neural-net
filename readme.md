# Image recognition in C

Heavily inspirited by Tsoding stream.

```console
./build.sh
./main
feh weights.ppm
```

the weights are visualized and stored saved to the weights.ppm

# my analysis

The algorithm I made is similar to a convolutional neural network, it greates a kernel of weights and produces a element-wice dot product.
The only thing that is *really* different is that there is only one layer, and that there is no pooling in this layer.

The weight matrix is simply a 1x1 size of the input layer and multiplying the individual scalars with each other to produce an output.
This is the reason it's so easy to visualize the way that I have done. 

![AI brain](http://139.162.160.227/static-file/Machine-learning.gif)
## hyperparameters

So with this model being much more 'basic' we already remove some hyperparameters that would otherwise increase model-complexity. The hyperparameters in question are padding and pooling, which are unique to CNNs.

the hyperparameters that we have the option to tune are:
- TEST\_SEED : [the random generator seed for the test data]

- TRAIN\_SEED : [the random generator seed for the train data]

- HEIGHT : [the height of the matrix, synanomous with N]

- WIDTH : [the width of the matrix, synanomous with M]

- PPM\_SCALAR : [the scalar to upscale the .ppm debug images]

- SAMPLE\_SIZE : [the size of our sample random generation, it produces 2 samples each size]

- BIAS : [the bias]

- EPOCHS : [the amount of training cycles. I have a callback for early stopping in the model]


# references:
* [tsoding stream](https://www.twitch.tv/tsoding)
* [CNN](https://en.wikipedia.org/wiki/Convolutional_neural_network)
* [ppm format](http://netpbm.sourceforge.net/doc/ppm.html)


