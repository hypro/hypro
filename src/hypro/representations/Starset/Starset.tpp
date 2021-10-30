#pragma once
#include "Starset.h"

namespace hypro {


template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation>::StarsetT() 
:mCenter(vector_t<Number>::Zero(1)) ,mGenerator(matrix_t<Number>::Zero(1,1)),constraints(){

}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation>::StarsetT(const vector_t<Number>& center,const matrix_t<Number>& shapematrix,const vector_t<Number>& limits,const matrix_t<Number>& generator)
:mCenter(center),mGenerator(generator), constraints(shapematrix,limits)
{

}
template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation>::StarsetT(const vector_t<Number>& center,const matrix_t<Number>& generator, const Representation Constraints)
:mCenter(center),mGenerator(generator), constraints(Constraints)
{

}
//only with
template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation>::StarsetT(const matrix_t<Number>& shapematrix,const vector_t<Number>& limits)
:mCenter(vector_t<Number>::Zero(shapematrix.cols())),mGenerator(matrix_t<Number>::Identity(shapematrix.cols(),shapematrix.cols())),constraints(shapematrix,limits)
{

}
template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation>::StarsetT(Representation Constraints)
:mCenter(vector_t<Number>::Zero(Constraints.matrix().cols())),mGenerator(matrix_t<Number>::Identity(Constraints.matrix().cols(),Constraints.matrix().cols())),constraints(Constraints)
{

}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation>::StarsetT( const StarsetT<Number, Converter, Setting,Representation>& orig ) 
    :GeometricObjectBase(orig),
    mCenter(orig.center()),mGenerator(orig.generator()),constraints(orig.constraintss())
{

}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation>::StarsetT( StarsetT<Number, Converter, Setting,Representation>&& orig )
    :GeometricObjectBase(orig),
    mCenter(orig.center()),mGenerator(orig.generator()),constraints(orig.constraintss())
    {


}

//new getters
template <typename Number, typename Converter, typename Setting, class Representation>
vector_t<Number> StarsetT<Number, Converter, Setting,Representation>::center() const {
    return mCenter;
}
template <typename Number, typename Converter, typename Setting, class Representation>
vector_t<Number> StarsetT<Number, Converter, Setting,Representation>::limits() const {
    return constraints.vector();
}
template <typename Number, typename Converter, typename Setting, class Representation>
matrix_t<Number> StarsetT<Number, Converter, Setting,Representation>::shape() const {
    return constraints.matrix();
}
template <typename Number, typename Converter, typename Setting, class Representation>
matrix_t<Number> StarsetT<Number, Converter, Setting,Representation>::generator() const {
    return mGenerator;
}

template <typename Number, typename Converter, typename Setting, class Representation>
Representation StarsetT<Number, Converter, Setting,Representation>::constraintss() const {
    return constraints;
}

template <typename Number, typename Converter, typename Setting, class Representation>
bool StarsetT<Number, Converter, Setting,Representation>::empty() const {
    std::cout<<"bura mi patliyo"<<std::endl;
    if(mGenerator.isZero(0.0000001)){
        return 1;
    }
    return constraints.empty();

}

template <typename Number, typename Converter, typename Setting, class Representation>
Number StarsetT<Number, Converter, Setting,Representation>::supremum() const {

}

template <typename Number, typename Converter, typename Setting, class Representation>
std::vector<Point<Number>> StarsetT<Number, Converter, Setting,Representation>::vertices() const {
    std::cout<<"vertices"<<std::endl;
    std::vector<Point<Number>> res; 
    std::cout<<"vertices"<<std::endl;
    auto placeholder= constraints.vertices();
	for ( auto point : placeholder ) {
        point=point.affineTransformation(mGenerator,mCenter);
        res.push_back(point);
    }
    return res;
}

template <typename Number, typename Converter, typename Setting, class Representation>
EvaluationResult<Number> StarsetT<Number, Converter, Setting,Representation>::evaluate( const vector_t<Number>& _direction, bool ) const {

}

template <typename Number, typename Converter, typename Setting, class Representation>
std::vector<EvaluationResult<Number>> StarsetT<Number, Converter, Setting,Representation>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {

}

template <typename Number, typename Converter, typename Setting, class Representation>
std::size_t StarsetT<Number, Converter, Setting,Representation>::dimension() const {
    return mGenerator.rows();
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::removeRedundancy() {
    std::string s= typeid(Representation).name();
    std::cout<<"sSS"<<std::endl;
    if(s=="N5hypro10HPolytopeTIdNS_9ConverterIdEENS_16HPolytopeSettingEEE"){
            std::cout<<"sSS"<<std::endl;

        auto intermediate=Converter::toHPolytope(*this );
        intermediate=intermediate.removeRedundancy();
        auto tmp=Converter::toStarset(intermediate);

        return tmp;
    }
    else{
        return *this;
    }

}

template <typename Number, typename Converter, typename Setting, class Representation>
std::size_t StarsetT<Number, Converter, Setting,Representation>::size() const {

    return 1;
}

template <typename Number, typename Converter, typename Setting, class Representation>
const StarsetT<Number, Converter, Setting,Representation>& StarsetT<Number, Converter, Setting,Representation>::reduceNumberRepresentation() {
        std::cout<<"ssss5"<<std::endl;

}

template <typename Number, typename Converter, typename Setting, class Representation>
std::pair<CONTAINMENT, StarsetT<Number, Converter, Setting,Representation>> StarsetT<Number, Converter, Setting,Representation>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
    //satisfiesda cevir halfspacei ayni koordinatta yaz hpolye ver
    std::cout<<"ssss"<<std::endl;

    StarsetT<Number, Converter, Setting,Representation> star=this->intersectHalfspace(rhs);
    StarsetT<Number, Converter, Setting,Representation> star2=StarsetT<Number, Converter, Setting,Representation>(constraints) ;
    std::string s= typeid(Representation).name();
    std::cout<<"s"<<std::endl;
    Representation intermediate;
    if(s=="N5hypro10HPolytopeTIdNS_9ConverterIdEENS_16HPolytopeSettingEEE"){
        intermediate  = Converter::toHPolytope(star2);
    }
    else{
        intermediate  = Converter::toBox(star2);
    }
    //std::cout<<std::get<0>(intermediate.satisfiesHalfspace(calculateHalfspace(rhs)))<<std::endl;
    return std::make_pair(std::get<0>(intermediate.satisfiesHalfspace(star.calculateHalfspace(rhs))),std::move( star ));
}

template <typename Number, typename Converter, typename Setting, class Representation>
std::pair<CONTAINMENT, StarsetT<Number, Converter, Setting,Representation>> StarsetT<Number, Converter, Setting,Representation>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
        std::cout<<"satisfies"<<std::endl;

    if(this->empty()){
        return std::make_pair( CONTAINMENT::NO, std::move(*this ) );
    }
     std::cout<<"satisfies"<<std::endl;

    std::pair<matrix_t<Number>, vector_t<Number>> zz=this->calculateHalfspaces(_mat ,_vec);
    std::cout<<"satisfies"<<std::endl;

    //buraya ayar cek direk 
    auto ans=(constraints.satisfiesHalfspaces(std::get<0>(zz),std::get<1>(zz))); 
    
    StarsetT<Number, Converter, Setting,Representation> star=StarsetT<Number, Converter, Setting,Representation>(mCenter,mGenerator,std::get<1>(ans));

    if(CONTAINMENT::PARTIAL==std::get<0>(ans)){
        std::cout<<"Partial"<<std::endl;
        return  std::make_pair( std::get<0>(ans),star.removeRedundancy());
    }
    return std::make_pair(std::get<0>(ans),std::move(star));

}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::projectOn( const std::vector<std::size_t>& dimensions ) const {
        std::cout<<"ssss4"<<std::endl;

}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::linearTransformation( const matrix_t<Number>& A ) const {
    std::cout<<"affine1q11"<<std::endl;

    matrix_t<Number> newGenerator = matrix_t<Number>(mGenerator.rows(),mGenerator.cols());
    newGenerator=A*mGenerator;
    vector_t<Number> newCenter=A*mCenter;
    
    return StarsetT<Number, Converter, Setting,Representation>(newCenter,newGenerator,constraints);
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
    std::cout<<"ssss7"<<std::endl;
    
    if ( !this->empty()){
        std::cout<<"affine"<<std::endl;
        std::cout<<"mat"<<A<<"vec"<<b<<std::endl;
        StarsetT<Number, Converter, Setting,Representation> tmp=StarsetT<Number, Converter, Setting,Representation>(A*(mCenter)+b,A*mGenerator,constraints);
        std::cout<<"affine3"<<std::endl;

        return tmp;
    }
    return *this;
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::minkowskiSum( const StarsetT<Number, Converter, Setting,Representation>& rhs ) const {
     //assuming same dimension
    std::cout<<"minkows"<<std::endl;
    //std::cout<< "bu limits " << this->limits()<<std::endl;
    //std::cout<< "bu center    " << this->center()<<std::endl;
    //std::cout<< "bu generator " << this->generator()<<std::endl;
    //std::cout<< "bu shape " << this->shape()<<std::endl;
    if(rhs.dimension()==0){
        return *this;
    }
    if(this->dimension()==0){
        return rhs;
    }
    std::string s= typeid(Representation).name();
    if(s!="N5hypro10HPolytopeTIdNS_9ConverterIdEENS_16HPolytopeSettingEEE"){
        auto intermediate=Converter::toBox(*this );
        return Converter::toStarset(intermediate);
    }
    matrix_t<Number> newmGenerator=matrix_t<Number>::Zero(mGenerator.rows(),mGenerator.cols()+rhs.generator().cols()); 
    matrix_t<Number> newmShapeMatrix=matrix_t<Number>::Zero(constraints.matrix().rows()+rhs.shape().rows(),constraints.matrix().cols()+rhs.shape().cols());
    vector_t<Number> newmLimits=vector_t<Number>::Zero(constraints.vector().rows()+rhs.limits().rows());
    //setting new generator matrix
    newmGenerator.block(0,0,mGenerator.rows(),mGenerator.cols())=mGenerator;
    newmGenerator.block(0, mGenerator.cols(), rhs.generator().rows() , rhs.generator().cols())=rhs.generator();

    //setting new shape Matrix  
    newmShapeMatrix.topLeftCorner(constraints.matrix().rows(),constraints.matrix().cols())=constraints.matrix();
    newmShapeMatrix.bottomRightCorner(rhs.shape().rows(),rhs.shape().cols())=rhs.shape();

    //setting new limits vector
    newmLimits.head(constraints.vector().rows())=constraints.vector();
    newmLimits.tail(rhs.limits().rows())=rhs.limits();
    //setting new center
    vector_t<Number> newmCenter=mCenter+rhs.center();
    
    //auto intermediate=Converter::toHPolytope(*this );

    //auto intermediate2=Converter::toHPolytope(rhs );
    //std::cout<<"generator"<<newmGenerator<<std::endl;

    return StarsetT<Number, Converter, Setting,Representation>(newmCenter,newmShapeMatrix,newmLimits,newmGenerator).removeRedundancy();
  
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::intersect( const StarsetT<Number, Converter, Setting,Representation>& rhs ) const {
    std::cout<<"intersect stars"<<std::endl;
    //yapilacak
    auto intermediate  = Converter::toHPolytope(*this );
    auto intermediate2 = Converter::toHPolytope(  rhs );
    return Converter::toStarset(intermediate.intersect(intermediate2)).removeRedundancy();
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::intersectHalfspace( const Halfspace<Number>& hspace ) const {
    std::cout<<"intersect  "<<std::endl;
    auto intermediate=this->calculateHalfspace(hspace);
	return StarsetT<Number, Converter, Setting,Representation>(mCenter,mGenerator, constraints.intersectHalfspace(intermediate));
}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
    std::cout<<"intersect halfspaces"<<std::endl;
    return StarsetT<Number, Converter, Setting,Representation>(mCenter,mGenerator,constraints.intersectHalfspaces(_mat,_vec));
}

template <typename Number, typename Converter, typename Setting, class Representation>
bool StarsetT<Number, Converter, Setting,Representation>::contains( const Point<Number>& point ) const {
    std::cout<<"contind"<<std::endl;

    return constraints.contains(point.affineTransformation(this->generator(),mCenter));
}

template <typename Number, typename Converter, typename Setting, class Representation>
bool StarsetT<Number, Converter, Setting,Representation>::contains( const StarsetT<Number, Converter, Setting,Representation>& Starset ) const {
    std::cout<<"containstar"<<std::endl;
    auto intermediate=Converter::toHPolytope(*this );
    auto rhs=Converter::toHPolytope(Starset);
    return intermediate.contains(rhs);
}
template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::unite( const StarsetT<Number, Converter, Setting,Representation>& rhs ) const {
    /*The method implemented here is similar to the method proposed by
     * Prof. Girard for Zonotope.
     * Reachability of Uncertain Linear Systems Using
     *      Zonotopes, Antoin Girard, HSCC2005 
     * Output is an overapproximation of convex hull of two star sets
     * Explanation for this method is written in Bachelor thesis of Dogu Tamgac*/
    std::cout<<"uniteeee"<<std::endl;
    std::cout<<"contind"<<std::endl;
    
    std::string s= typeid(Representation).name();
    if(s=="N5hypro10HPolytopeTIdNS_9ConverterIdEENS_16HPolytopeSettingEEE"){
        //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto intermediate=Converter::toHPolytope(*this );
        auto intermediate2=Converter::toHPolytope(rhs );
        auto x = Converter::toStarset(intermediate.unite(intermediate2));
        //std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time" << std::endl;
        //std::cout<<"x,generator"<<x.generator()<<std::endl;
        return x;
    }
    else{
        //burdayim
        auto intermediate=Converter::toBox(*this );
        auto intermediate2=Converter::toBox(rhs );
        auto x = Converter::toStarset(intermediate.unite(intermediate2));
        //std::cout<<"x,generator"<<x.generator()<<std::endl;
        return x;
        ////std::cout<<placeholder<<std::endl;

    }
    //std::cout<< "bu intersect " << this->limits()<<std::endl;
    //std::cout<< "bu center    " << this->center()<<std::endl;
    //std::cout<< "bu generator " << this->generator()<<std::endl;
    //std::cout<< "bu shape " << this->shape()<<std::endl;
    auto tmp1=StarsetT<Number, Converter, Setting,Representation>(this->center(),this->generator(),this->constraintss()).removeRedundancy();
    auto tmp2=StarsetT<Number, Converter, Setting,Representation>(rhs.center(),rhs.generator(),rhs.constraintss()).removeRedundancy();
      //return Converter::toStarset(intermediate.unite(intermediate2).removeRedundancy());
     /*matrix_t<Number> newmGenerator=matrix_t<Number>::Zero(mGenerator.rows(),mGenerator.cols()+rhs.generator().cols()); 
     matrix_t<Number> newmShapeMatrix=matrix_t<Number>::Zero(this->shape().rows()+rhs.shape().rows(),this->shape().cols()+rhs.shape().cols());
     vector_t<Number> newmLimits=vector_t<Number>::Zero(this->limits().rows()+rhs.limits().rows());
    
     vector_t<Number> newmCenter=mCenter-rhs.center();
     newmGenerator.block(0,0,mGenerator.rows(),mGenerator.cols())=mGenerator;
     newmGenerator.block(0, mGenerator.cols(), rhs.generator().rows() , rhs.generator().cols())=-rhs.generator();
     
     newmShapeMatrix.topLeftCorner(this->shape().rows(),this->shape().cols())=this->shape();
     newmShapeMatrix.bottomRightCorner(rhs.shape().rows(),rhs.shape().cols())=rhs.shape();
     
     newmLimits.head(this->limits().rows())=this->limits();
     newmLimits.tail(rhs.limits().rows())=rhs.limits();
     auto buff=rhs.minkowskiSum( StarsetT<Number, Converter, Setting,Representation>(newmCenter,newmShapeMatrix,newmLimits,newmGenerator));//.removeRedundancy() ;
     */
     matrix_t<Number> newmGenerator=matrix_t<Number>::Zero(tmp1.generator().rows(),tmp1.generator().cols()+tmp2.generator().cols()); 
     matrix_t<Number> newmShapeMatrix=matrix_t<Number>::Zero(tmp1.shape().rows()+tmp2.shape().rows(),tmp1.shape().cols()+tmp2.shape().cols());
     vector_t<Number> newmLimits=vector_t<Number>::Zero(tmp1.limits().rows()+tmp2.limits().rows());
     //std::cout<<"newGenerator="<<newmGenerator<<std::endl;
     vector_t<Number> newmCenter=tmp1.center()-tmp2.center();
     newmGenerator.block(0,0,tmp1.generator().rows(),mGenerator.cols())=tmp1.generator();
     newmGenerator.block(0, tmp1.generator().cols(), tmp2.generator().rows() , tmp2.generator().cols())=-tmp2.generator();
     
     newmShapeMatrix.topLeftCorner(tmp1.shape().rows(),tmp1.shape().cols())=tmp1.shape();
     newmShapeMatrix.bottomRightCorner(tmp2.shape().rows(),tmp2.shape().cols())=tmp2.shape();
     
     newmLimits.head(tmp1.limits().rows())=tmp1.limits();
     newmLimits.tail(tmp2.limits().rows())=tmp2.limits();
     auto buff=tmp2.minkowskiSum( StarsetT<Number, Converter, Setting,Representation>(newmCenter,newmShapeMatrix,newmLimits,newmGenerator));//.removeRedundancy() ;
     
     //std::cout<< "bu intersect " << buff.limits()<<std::endl;
     //std::cout<< "bu center    " << buff.center()<<std::endl;
     //std::cout<< "bu generator " << buff.generator()<<std::endl;
     //std::cout<< "bu shape " << buff.shape()<<std::endl;
     return buff;

}

template <typename Number, typename Converter, typename Setting, class Representation>
StarsetT<Number, Converter, Setting,Representation> StarsetT<Number, Converter, Setting,Representation>::unite( const std::vector<StarsetT<Number, Converter, Setting,Representation>>& Starsets ) {
    std::cout<<"unite2"<<std::endl;
    StarsetT<Number, Converter, Setting,Representation> star= StarsetT<Number, Converter, Setting,Representation>(Starsets[0].center(),Starsets[0].generator(),Starsets[0].constraintss());
    for(int i=1;i<Starsets.size();i++){
        star=star.unite(Starsets[i]);
    }
    return star;
}

template <typename Number, typename Converter, typename Setting, class Representation>
void StarsetT<Number, Converter, Setting,Representation>::reduceRepresentation() {
    std::cout<<"ssss10"<<std::endl;
  
}
template <typename Number, typename Converter, typename Setting, class Representation>
 Halfspace<Number> StarsetT<Number, Converter, Setting,Representation>::calculateHalfspace( const Halfspace<Number>& hspace ) const{
    std::cout<<"elalem"<<std::endl;
    matrix_t<Number> temp=matrix_t<Number>(1,1);
    temp(0,0)=hspace.offset();
    Halfspace<Number> hp1((hspace.normal().transpose() *this->generator()),(temp-(hspace.normal().transpose())*(this->center()))(0,0) );
    return hp1;
 }
template <typename Number, typename Converter, typename Setting, class Representation>
std::pair<matrix_t<Number>, vector_t<Number>> StarsetT<Number, Converter, Setting,Representation>::calculateHalfspaces(const matrix_t<Number>& _mat, const vector_t<Number>& _vec  ) const{
    std::pair<matrix_t<Number>, vector_t<Number>> zulu=std::make_pair(_mat*this->generator(),_vec-vector_t<Number>(_mat*this->center()));
    return zulu;
}

template <typename Number, typename Converter, typename Setting, class Representation>
void StarsetT<Number, Converter, Setting,Representation>::clear() {

}

}  // namespace hypro
