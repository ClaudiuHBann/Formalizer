using Tensorflow;
using Tensorflow.Keras.Layers;
using Tensorflow.Keras.ArgsDefinition;
using Tensorflow.Operations.Initializers;

namespace Formalizer
{
/*
    Encoder model takes a input sequence and returns Encoder outputs as encoder_final_hidden_state,
    encoder_final_current_state
*/
internal class Encoder : Model
{
    private const int DEFAULT_INITIALIZER_SEED = 859;

    private readonly int _inputVocabularySize;
    private readonly int _lstmSize;
    private readonly int _inputLength;

    private Embedding _embedding;
    private LSTM _lstm1;
    private LSTM _lstm2;

    private Tensor _encOutput;
    private Tensor _lastHiddenState;
    private Tensor _lastCurrentState;

    private Tensor _firstHiddenState;
    private Tensor _firstCurrentState;

    public Encoder(int inputVocabularySize, int lstmSize, int inputLength) : base(new ModelArgs())
    {
        _inputVocabularySize = inputVocabularySize;
        _lstmSize = lstmSize;
        _inputLength = inputLength;

        _embedding = new Embedding(new EmbeddingArgs() {
            InputDim = _inputVocabularySize,
            OutputDim = _inputVocabularySize,
            EmbeddingsInitializer = new RandomNormal(0, 1, DEFAULT_INITIALIZER_SEED),
            InputLength = _inputLength,
            MaskZero = true,
            Name = "Encoder_Embedding",
        });

        var lstmArgs = new LSTMArgs() {
            Units = _lstmSize,
            ReturnState = true,
            ReturnSequences = true,
            KernelInitializer = new GlorotUniform(DEFAULT_INITIALIZER_SEED),
            RecurrentInitializer = new Orthogonal(DEFAULT_INITIALIZER_SEED),
        };

        lstmArgs.Name = "Encoder_LSTM1";
        _lstm1 = new LSTM(lstmArgs);

        lstmArgs.Name = "Encoder_LSTM2";
        _lstm2 = new LSTM(lstmArgs);
    }

    /*
        This method takes a sequence input and the initial states of the Encoder as inputs.
        Sequence input is passed to the Embedding layer and initial states are passed to the LSTM layer of the Encoder
        model. It returns Encoder outputs as last time step's hidden and current states.
    */
    public Tensors Call(Tensor input)
    {
        var inputSequence = input[0];
        var states = input[1];
        var inputEmbedded = _embedding.Apply(inputSequence);

        var resultLSTM1 = _lstm1.Apply(inputEmbedded, states);
        _encOutput = resultLSTM1[0];
        _lastHiddenState = resultLSTM1[1];
        _lastCurrentState = resultLSTM1[2];

        var resultLSTM2 = _lstm2.Apply(_encOutput, [_lastHiddenState, _lastCurrentState]);
        _encOutput = resultLSTM2[0];
        _lastHiddenState = resultLSTM2[1];
        _lastCurrentState = resultLSTM2[2];

        return [_encOutput, _lastHiddenState, _lastCurrentState];
    }

    /*
        Given a batch size this method will return intial hidden state and intial current state.
        If batch size is 32, Hidden state is zeros of size [32,lstm_units], current state is zeros is of size
        [32,lstm_units]
    */
    public Tensors InitializeStates(int batchSize)
    {
        _firstHiddenState = tf.zeros(new Shape([batchSize, _lstmSize]));
        _firstCurrentState = tf.zeros(new Shape([batchSize, _lstmSize]));

        return [_firstHiddenState, _firstCurrentState];
    }
}
}
