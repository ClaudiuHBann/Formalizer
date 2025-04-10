using Tensorflow;
using Tensorflow.Keras;
using Tensorflow.Keras.Layers;
using Tensorflow.Keras.ArgsDefinition;

namespace Formalizer
{
/*
    The EncoderDecoder Model initializes both Encoder and Decoder Models and outputs normalized probabilties of the
    tokens in target vocabulary.
*/
internal class EncoderDecoder : Model
{
    private readonly int _inputVocabularySize;
    private readonly int _outputVocabularySize;
    private readonly int _lstmSize;
    private readonly int _inputLength;
    private readonly int _batchSize;

    private Encoder _encoder;
    private Decoder _decoder;
    private Dense _dense;

    /*
        This method intializes the both the Encoder and Decoder models
    */
    public EncoderDecoder(int inputVocabularySize, int outputVocabularySize, int lstmSize, int inputLength,
                          int batchSize)
        : base(new ModelArgs())
    {
        _inputVocabularySize = inputVocabularySize;
        _outputVocabularySize = outputVocabularySize;
        _lstmSize = lstmSize;
        _inputLength = inputLength;
        _batchSize = batchSize;

        _encoder = new Encoder(_inputVocabularySize, _lstmSize, _inputLength);
        _decoder = new Decoder(_outputVocabularySize, _lstmSize, _inputLength);
        _dense = new Dense(new DenseArgs() {
            Units = _outputVocabularySize,
            Activation = tf.keras.activations.Softmax,
        });
    }

    /*
        This method takes data from data pipeline in tuples of length 2, where first is encoder_inp and second is
        decoder_inp encoder_inp is fed to Encoder model object alongwith initial states whereas decoder_inp is fed to
        decoder model object alongwith Encoder last hidden and current states. The Model then returns normalized output
        probabilities of tokens in target vocabulary.
    */
    public Tensors Call(Tensor data)
    {
        var encryptedInput = data[0];
        var decryptedInput = data[1];

        var initialState = _encoder.InitializeStates(_batchSize);

        var encoderResult = _encoder.Apply([encryptedInput, initialState]);
        var encoderOutput = encoderResult[0];
        var encoderHidden = encoderResult[1];
        var encoderCurrent = encoderResult[2];

        var decoderResult = _decoder.Apply([decryptedInput, new Tensors(encoderHidden, encoderCurrent)]);
        var decoderOutput = decoderResult[0];
        var decoderHidden = decoderResult[1];
        var decoderCurrent = decoderResult[2];

        return _dense.Apply(decoderOutput);
    }
}
}
