template <size_t N>
class hamming_code
{
    static constexpr auto M = [] {
        size_t r = 0;
        while((1ULL<<r)<N+r+1) r++;
        return r;
    }();
public:
    static constexpr auto length = N+M;
    static constexpr auto encode(bitset<N> msg)
    {
        bitset<N+M+1> code;
        for(size_t i=1,j=0;i<=N+M;i++)
            if(!has_single_bit(i))
                code[i] = msg[j++];
        for(size_t i=1;i<=N+M;i<<=1)
            for(size_t j=1;j<=N+M;j++)
                if(i&j) code[i] = code[i]^code[j];
        return code;
    }
    static constexpr auto decode(bitset<N+M+1> code)
    {
        size_t err = 0;
        for(size_t i=1;i<=N+M;i++)
            if(code.test(i)) err ^= i;
        if(err) code.flip(err);
        bitset<N> msg;
        for(size_t i=1,j=0;i<=N+M;i++)
            if(!has_single_bit(i))
                msg[j++] = code[i];
        return msg;
    }
};
