
namespace hypro
{

template<typename To, typename From>
To convert(const From& in) {
    return;
}

template<typename Number, typename OutSettings, typename InSettings>
SupportFunctionT<Number,Converter<Number>,OutSettings> convert(const In<Number,Converter<Number>,InSettings>& in) {
    return toSupportFunction<OutSettings>(in);
}

template<typename Number, typename OutSettings, typename InSettings>
BoxT<Number,Converter<Number>,OutSettings> convert(const In<Number,Converter<Number>,InSettings>& in) {
    return toBox<OutSettings>(in);
}

} // hypro
