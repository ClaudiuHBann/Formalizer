using Tensorflow;
using Tensorflow.Keras.Layers;
using Tensorflow.Keras.ArgsDefinition;

namespace Formalizer
{
/*
    Decoder model takes an encoded vector of input sequence and returns output sequence
*/
internal class Decoder : Model
{
    private readonly int _outputVocabularySize;
    private readonly int _lstmSize;
    private readonly int _inputLength;

    private Embedding _embedding;
    private LSTM _lstm;

    private Tensor _decryptedOutput;
    private Tensor _lastHiddenState;
    private Tensor _lastCurrentState;

    /*
        This method intializes the Encoder model.
    */
    public Decoder(int outputVocabularySize, int lstmSize, int inputLength) : base(new ModelArgs())
    {
        _outputVocabularySize = outputVocabularySize;
        _lstmSize = lstmSize;
        _inputLength = inputLength;

        _embedding = new Embedding(new EmbeddingArgs() {
            InputDim = _outputVocabularySize,
            OutputDim = _outputVocabularySize,
            InputLength = _inputLength,
            MaskZero = true,
            Name = "embedding_layer_decoder",
        });

        _lstm = new LSTM(new LSTMArgs() {
            Units = _lstmSize,
            ReturnState = true,
            ReturnSequences = true,
            Name = "Encoder_LSTM",
        });
    }

    /*
        This method takes a sequence input and the last current state of the Encoder as inputs.
        Sequence input is passed to the Embedding layer and Encoder current states are passed to the LSTM layer of the
        Decoder model. It returns Decoder outputs as last time step's hidden and current states.
    */
    public Tensors Call(Tensor input)
    {
        var inputSequence = input[0];
        var states = input[1];

        var targetEmbedd = _embedding.Apply(inputSequence);

        var resultLSTM = _lstm.Apply(targetEmbedd, states);
        _decryptedOutput = resultLSTM[0];
        _lastHiddenState = resultLSTM[1];
        _lastCurrentState = resultLSTM[2];

        return [_decryptedOutput, _lastHiddenState, _lastCurrentState];
    }
}
}
