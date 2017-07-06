static const int A = 48271;
static const int M = 2147483647;
static const int Q = M/A ;
static const int R = M%A ;

class Random
{
public :
    explicit Random(int initialVal=1);

    int RandomInt();
    double Random0_1();
    int RandomInt(int low,int high);
private :
    int state;
};

Random::Random(int initialVal)
{
    if(initialVal < 0)
        initialVal += M;
    
    state = initialVal;
    if(state==0)
        state=1;
}

int Random::RandomInt()
{
    int tmpState = A*( state % Q ) - R * (state / Q);

    if(tmpState > 0)
        state = tmpState;
    else
        state = tmpState + M;

    return state;
}
//生成0.0到1.0之间的随机小数
double Random::Random0_1()
{
    return (double)RandomInt()/M;
}
//生成low到high之间的随机整数
int Random::RandomInt(int low, int high)
{
    int range = high - low;
    
    return low+RandomInt()%range;
}