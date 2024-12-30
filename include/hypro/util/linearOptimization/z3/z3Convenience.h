/*
 * Copyright (c) 2021-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

//
// Created by stefan on 30.06.16.
//
// TODO Johannes: clean me up!
//

#pragma once
#include "hypro/flags.h"
#include "../../../datastructures/Point.h"
#include "../../../types.h"
#include "../EvaluationResult.h"

#include <hypro/flags.h>

#ifdef HYPRO_USE_Z3
#include "../../../types.h"
#include "z3Context.h"

#include <thread>

namespace hypro {

template <typename Number>
static z3::expr_vector createFormula( const matrix_t<Number>& _constraints, const vector_t<Number> _constants, const std::vector<carl::Relation>& relations, z3Context& c ) {
    // std::cout << __func__ << _constraints << " \n\n " << _constants << std::endl;

    z3::expr_vector constraints( c );
    z3::expr_vector variables( c );
    // std::cout << "Variables.size() " << variables.size() << std::endl;
    for ( unsigned i = 0; i < _constraints.cols(); ++i ) {
        z3::expr var( c );
        const char* varName = ( "x_" + std::to_string( i ) ).c_str();
        var = c.real_const( varName );
        variables.push_back( var );
    }

    for ( unsigned i = 0; i < _constraints.rows(); ++i ) {
        z3::expr polynomial( c );
        polynomial = c.int_val( 0 );
        for ( unsigned j = 0; j < _constraints.cols(); ++j ) {
            z3::expr coeff( c );
            coeff = c.real_val( ( carl::convert<Number, mpq_class>( _constraints( i, j ) ) ) );

            z3::expr term( c );
            term = variables[j] * coeff;
            polynomial = polynomial + term;
        }
        z3::expr constant = c.real_val( carl::convert<Number, mpq_class>( _constants( i ) ) );
        z3::expr constraint( c );
        switch ( relations[i] ) {
            case carl::Relation::LEQ:
                constraint = polynomial <= constant;
                break;
            case carl::Relation::GEQ:
                constraint = polynomial >= constant;
                break;
            case carl::Relation::EQ:
                constraint = polynomial == constant;
                break;
            case carl::Relation::LESS:
                constraint = polynomial < constant;
                break;
            default:
                assert( false );
        }
        constraints.push_back( constraint );
    }

    return constraints;
}

template <typename Number>
static z3::expr createFormula( const Point<Number>& _point, const matrix_t<Number>& _constraints, const vector_t<Number>& _constants, 
                               const std::vector<carl::Relation>& relations, z3Context& c ) {
    z3::expr formula( c );
    formula = c.bool_val( true );
    z3::expr pointConstraint( c );
    pointConstraint = c.int_val( 0 );

    std::vector<z3::expr> variables;
    for ( unsigned i = 1; i <= _constraints.cols(); ++i ) {
        std::string name = "x_" + std::to_string( i );
        variables.push_back( c.real_const( name.c_str() ) );
    }

    for ( unsigned d = 0; d < _point.dimension(); ++d ) {
        if ( _point.at( d ) != carl::constant_zero<Number>::get() ) {
            pointConstraint = pointConstraint + c.real_val( carl::convert<Number, mpq_class>( -_point.at( d ) ) ) + variables.at( d );
        }
    }

    formula = formula && ( pointConstraint == 0 );

    for ( unsigned i = 0; i < _constraints.rows(); ++i ) {
        z3::expr constraint( c );
        constraint = c.int_val( 0 );
        for ( unsigned j = 0; j < _constraints.cols(); ++j ) {
            if ( _constraints( i, j ) != carl::constant_zero<Number>::get() ) {
                constraint = constraint + variables.at( j ) * ( c.real_val( carl::convert<Number, mpq_class>( _constraints( i, j ) ) ) );
            }
        }
        z3::expr constant = c.real_val( carl::convert<Number, mpq_class>( _constants( i ) ) );
        switch ( relations[i] ) {
            case carl::Relation::LEQ:
                constraint = constraint <= constant;
                break;
            case carl::Relation::GEQ:
                constraint = constraint >= constant;
                break;
            case carl::Relation::EQ:
                constraint = constraint == constant;
                break;
            default:
                assert( false );
        }
        formula = formula && constraint;
    }

    return formula;
}

template <typename Number>
static z3::expr createFormula( const Point<Number>& _point, const matrix_t<Number>& _constraints, const vector_t<Number>& _constants, 
                               const matrix_t<Number>& _linTransform, const vector_t<Number>& _offset, z3Context& c ) {

    // Build formula for Cx <= d and y = Ax + b, such that y is given and find a satisfying assignment for x (if exists)

    z3::expr formula( c );
    formula = c.bool_val( true );

    std::vector<z3::expr> variables;
    for ( unsigned i = 0; i < _constraints.cols(); ++i ) {
        std::string name = "x_" + std::to_string( i );
        variables.push_back( c.real_const( name.c_str() ) );
    }
    // std::cout << variables << std::endl;

    for ( unsigned i = 0; i < _constraints.rows(); ++i ) {
        z3::expr constraint( c );
        constraint = c.int_val( 0 );
        for ( unsigned j = 0; j < _constraints.cols(); ++j ) {
            if ( _constraints( i, j ) != carl::constant_zero<Number>::get() ) {
                constraint = constraint + variables.at( j ) * ( c.real_val( carl::convert<Number, mpq_class>( _constraints( i, j ) ) ) );
            }
        }
        z3::expr constant = c.real_val( carl::convert<Number, mpq_class>( _constants( i ) ) );
        formula = formula && (constraint <= constant);
    }

    for ( unsigned i = 0; i < _linTransform.rows(); ++i ) {
        z3::expr constraint( c );
        constraint = c.int_val( 0 );
        for ( unsigned j = 0; j < _linTransform.cols(); ++j ) {
            if ( _linTransform( i, j ) != carl::constant_zero<Number>::get() ) {
                constraint = constraint + variables.at( j ) * ( c.real_val( carl::convert<Number, mpq_class>( _linTransform( i, j ) ) ) );
            }
        }
        z3::expr constant = c.real_val( carl::convert<Number, mpq_class>( _point.at( i ) ) ) - c.real_val( carl::convert<Number, mpq_class>( _offset( i ) ) );
        formula = formula && (constraint == constant);
    }

    // std::cout << "Formula: " << formula << std::endl;
    return formula;
}

template <typename Number>
static z3::expr createFormula(
 const Point<Number>& _point,
 const matrix_t<Number>& _constraints,
 const vector_t<Number>& _constants, 
 const matrix_t<Number>& _linTransform,
 const vector_t<Number>& _offset,
 z3Context& c,
 const int &_dimension,
 const carl::Relation &_relation 
 ) {

    // Build formula for Cx <= d and y = Ax + b, such that y is given and find a satisfying assignment for x (if exists)
    // Optional parameters change y = Ax+b for a single dimension i and bound v, such that Ax + b <=/==/>= y + v 

    z3::expr formula( c );
    formula = c.bool_val( true );

    std::vector<z3::expr> variables;
    for ( unsigned i = 0; i < _constraints.cols(); ++i ) {
        std::string name = "x_" + std::to_string( i );
        variables.push_back( c.real_const( name.c_str() ) );
    }
    // std::cout << variables << std::endl;

    for ( unsigned i = 0; i < _constraints.rows(); ++i ) {
        z3::expr constraint( c );
        constraint = c.int_val( 0 );
        for ( unsigned j = 0; j < _constraints.cols(); ++j ) {
            if ( _constraints( i, j ) != carl::constant_zero<Number>::get() ) {
                constraint = constraint + variables.at( j ) * ( c.real_val( carl::convert<Number, mpq_class>( _constraints( i, j ) ) ) );
            }
        }
        z3::expr constant = c.real_val( carl::convert<Number, mpq_class>( _constants( i ) ) );
        formula = formula && (constraint <= constant);
    }

    for ( unsigned i = 0; i < _linTransform.rows(); ++i ) {
        z3::expr constraint( c );
        constraint = c.int_val( 0 );
        for ( unsigned j = 0; j < _linTransform.cols(); ++j ) {
            if ( _linTransform( i, j ) != carl::constant_zero<Number>::get() ) {
                constraint = constraint + variables.at( j ) * ( c.real_val( carl::convert<Number, mpq_class>( _linTransform( i, j ) ) ) );
            }
        }
        z3::expr constant = c.real_val( carl::convert<Number, mpq_class>( _point.at( i ) ) ) - c.real_val( carl::convert<Number, mpq_class>( _offset( i ) ) );
        if (i == _dimension){
            switch ( _relation ) {
                case carl::Relation::LEQ:
                    formula = formula && (constraint <= constant);
                    break;
                case carl::Relation::GEQ:
                    formula = formula && (constraint >= constant);
                    break;
                case carl::Relation::EQ:
                   formula = formula && (constraint == constant);
                    break;
                case carl::Relation::LESS:
                    formula = formula && (constraint < constant);
                    break;
                case carl::Relation::GREATER:
                    formula = formula && (constraint > constant);
                    break;                
                default:
                    assert( false );
            }   
        } else {
            formula = formula && (constraint == constant);   
        }
    }

    // std::cout << "Formula: " << formula << std::endl;
    return formula;
}

template <typename Number>
static z3::expr createFormula(
 const Point<Number>& _point,
 const matrix_t<Number>& _constraints,
 const vector_t<Number>& _constants, 
 const matrix_t<Number>& _linTransform,
 const vector_t<Number>& _offset,
 z3Context& c,
 const std::vector<carl::Relation> &_relations 
 ) {

    // Build formula for Cx <= d and y = Ax + b, such that y is given and find a satisfying assignment for x (if exists)
    // Optional parameters change y = Ax+b for a single dimension i and bound v, such that Ax + b <=/==/>= y + v 

    z3::expr formula( c );
    formula = c.bool_val( true );

    std::vector<z3::expr> variables;
    for ( unsigned i = 0; i < _constraints.cols(); ++i ) {
        std::string name = "x_" + std::to_string( i );
        variables.push_back( c.real_const( name.c_str() ) );
    }
    // std::cout << variables << std::endl;

    for ( unsigned i = 0; i < _constraints.rows(); ++i ) {
        z3::expr constraint( c );
        constraint = c.int_val( 0 );
        for ( unsigned j = 0; j < _constraints.cols(); ++j ) {
            if ( _constraints( i, j ) != carl::constant_zero<Number>::get() ) {
                constraint = constraint + variables.at( j ) * ( c.real_val( carl::convert<Number, mpq_class>( _constraints( i, j ) ) ) );
            }
        }
        z3::expr constant = c.real_val( carl::convert<Number, mpq_class>( _constants( i ) ) );
        formula = formula && (constraint <= constant);
    }

    for ( unsigned i = 0; i < _linTransform.rows(); ++i ) {
        z3::expr constraint( c );
        constraint = c.int_val( 0 );
        for ( unsigned j = 0; j < _linTransform.cols(); ++j ) {
            if ( _linTransform( i, j ) != carl::constant_zero<Number>::get() ) {
                constraint = constraint + variables.at( j ) * ( c.real_val( carl::convert<Number, mpq_class>( _linTransform( i, j ) ) ) );
            }
        }
        z3::expr constant = c.real_val( carl::convert<Number, mpq_class>( _point.at( i ) ) ) - c.real_val( carl::convert<Number, mpq_class>( _offset( i ) ) );
        switch ( _relations[i] ) {
            case carl::Relation::LEQ:
                formula = formula && (constraint <= constant);
                break;
            case carl::Relation::GEQ:
                formula = formula && (constraint >= constant);
                break;
            case carl::Relation::EQ:
                formula = formula && (constraint == constant);
                break;
            case carl::Relation::LESS:
                formula = formula && (constraint < constant);
                break;
            case carl::Relation::GREATER:
                formula = formula && (constraint > constant);
                break;                
            default:
                assert( false && "Relation type undefined");
            }   
    }
    return formula;
}


template <typename Number>
static z3::expr createFormula(
 const matrix_t<Number>& _constraints,
 const vector_t<Number>& _constants, 
 const matrix_t<Number>& _linTransform,
 const vector_t<Number>& _offset,
 const std::vector<matrix_t<Number>> _rejectionConstraints,
 const std::vector<vector_t<Number>> _rejectionConstants,
 z3Context& c
 ) {
    // Assume starset < _offset, _linTransform, {variables | _constraints * variables <= _constants }>
    // Find a variable with (_constraints * variables <= _constants), such that for all {x | C*x <= d} \in rejectionSets: !(C*(_offset + _linTransform*variables) <= d) 
    // <=> !(C*_linTransform*variables <= d - C*_offset)

    z3::expr formula( c );
    formula = c.bool_val( true );

    //create variables
    std::vector<z3::expr> variables;
    for ( unsigned i = 0; i < _constraints.cols(); i++ ) {
        std::string name = "x_" + std::to_string( i );
        variables.push_back( c.real_const( name.c_str() ) );
    }
    //constrain variables to {variables | _constraints * variables <= _constants }
    for ( unsigned i = 0; i < _constraints.rows(); i++ ) {
        z3::expr constraint( c );
        constraint = c.int_val( 0 );
        for ( unsigned j = 0; j < _constraints.cols(); j++ ) {
            if ( _constraints( i, j ) != carl::constant_zero<Number>::get() ) {
                constraint = constraint + variables.at( j ) * ( c.real_val( carl::convert<Number, mpq_class>( _constraints( i, j ) ) ) );
            }
        }
        z3::expr constant = c.real_val( carl::convert<Number, mpq_class>( _constants( i ) ) );
        formula = formula && (constraint <= constant);
    }
    // !(C_0*_linTransform*variables <= d_0 - C_0*_offset) && ... && !(C_k*_linTransform*variables <= d_k - C_k*_offset)
    // !(C*_linTransform*variables <= d - C*_offset) <=> (C*_linTransform).row(l)*variables > (d - C*_offset).row(l)
    for (unsigned k = 0; k < _rejectionConstraints.size(); k++){
        z3::expr disjunction( c );
        disjunction = c.bool_val( false );
        matrix_t<Number> fullLinTransform = _rejectionConstraints[k] * _linTransform;
        vector_t<Number> fullOffset = _rejectionConstraints[k] * _offset;
        for ( unsigned i = 0; i < fullLinTransform.rows(); i++ ) {
            z3::expr constraint( c );
            constraint = c.int_val( 0 );
            for ( unsigned j = 0; j < fullLinTransform.cols(); j++ ) {
                if ( fullLinTransform( i, j ) != carl::constant_zero<Number>::get() ) {
                    constraint = constraint + variables.at( j ) * ( c.real_val( carl::convert<Number, mpq_class>( fullLinTransform( i, j ) ) ) );
                }
            }
            z3::expr constant = c.real_val( carl::convert<Number, mpq_class>( _rejectionConstants[k]( i ) ) ) - c.real_val( carl::convert<Number, mpq_class>( fullOffset( i ) ) );
            disjunction = disjunction || (constraint > constant);   
        }
        formula = formula && disjunction;
    }
    return formula;
}

template <typename Number>
static std::pair <z3::expr, z3::expr> createFormulaAndObjective(
 const matrix_t<Number>& _constraints,
 const vector_t<Number>& _constants, 
 const matrix_t<Number>& _linTransform,
 const vector_t<Number>& _offset,
 const std::vector<matrix_t<Number>> _rejectionConstraints,
 const std::vector<vector_t<Number>> _rejectionConstants,
 z3Context& c
 ) {
    // Assume starset < _offset, _linTransform, {variables | _constraints * variables <= _constants }>
    // Find a variable with (_constraints * variables <= _constants), such that for all {x | C*x <= d} \in rejectionSets: !(C*(_offset + _linTransform*variables) <= d) 
    // <=> !(C*_linTransform*variables <= d - C*_offset)

    z3::expr formula( c );
    z3::expr objective( c );
    objective = c.int_val(0);
    formula = c.bool_val( true );
    
    //create variables
    std::vector<z3::expr> variables;
    for ( unsigned i = 0; i < _constraints.cols(); i++ ) {
        std::string index = std::to_string( i );
        //x = s * (n/d) where s=1,-1 and n >= 0 and d >= 1 (n/d = |x|)
        //variables.push_back( c.real_const( ("x_" + index).c_str() ) ); 
        variables.push_back( c.int_const( ("s_" + index).c_str() ) ); 
        variables.push_back( c.int_const( ("n_" + index).c_str() ) );
        variables.push_back( c.int_const( ("d_" + index).c_str() ) );
    }
       
    //Set objective = \sum_{i} n_i + d_i
    //And add constraints for the variables
    for (unsigned i = 0 ; i < _constraints.cols(); i++){
        objective = objective + variables[i*3 + 1] +  variables[i*3 + 2];
        // x=s*(n/d) <=> x * s * d = n
        // formula = formula && (variables[i*4 + 0] * variables[i*4 + 1] * variables[i*4 + 3] == variables[i*4 + 2]);
        // s is the sign of x
        formula = formula && ((variables[i*3] == 1) || (variables[i*3] == -1)); 
        // n is the numerator of x and should be non-negativ for a meaningful objective (sign only influnced by s)
        formula = formula && (variables[i*3 + 1] >= 0);
        // d is the denominator of x and should be positive for a meaningful objective (sign only influnced by s + n/d defined)
        formula = formula && (variables[i*3 + 2] >= 1);
    }
    
    //Construct formula    
    //Constrain variables to {variables | _constraints * variables <= _constants }
    for ( unsigned i = 0; i < _constraints.rows(); i++ ) {

        z3::expr constraint( c );
        constraint = c.int_val( 0 );
        z3::expr constant( c );
        constant = c.real_val( carl::convert<Number, mpq_class>( _constants( i ) ) );

        for ( unsigned j = 0; j < _constraints.cols(); j++ ) {
            constant = constant * variables.at(j * 3 + 2);
            if ( _constraints( i, j ) != carl::constant_zero<Number>::get() ) {
                z3::expr summand( c );
                summand = ( c.real_val( carl::convert<Number, mpq_class>( _constraints( i, j ) ) ) ) * variables.at( j*3 ) * variables.at( j*3 +1);
                for (unsigned k = 0; k < _constraints.cols(); k++ ){
                    if(k != j){
                        summand = summand * variables.at(k * 3 + 2);
                    }
                }
                constraint = constraint + summand;
            }
        }
       
        formula = formula && (constraint <= constant);
    }
    
    // !(C_0*_linTransform*variables <= d_0 - C_0*_offset) && ... && !(C_k*_linTransform*variables <= d_k - C_k*_offset)
    // !(C*_linTransform*variables <= d - C*_offset) <=> (C*_linTransform).row(l)*variables > (d - C*_offset).row(l)
    for (unsigned index = 0; index < _rejectionConstraints.size(); index++){
        z3::expr disjunction( c );
        disjunction = c.bool_val( false );
        matrix_t<Number> fullLinTransform = _rejectionConstraints[index] * _linTransform;
        vector_t<Number> fullOffset = _rejectionConstraints[index] * _offset;

        for ( unsigned i = 0; i < fullLinTransform.rows(); i++ ) {
            z3::expr constraint( c );
            constraint = c.int_val( 0 );
            z3::expr constant (c);
            constant = c.real_val( carl::convert<Number, mpq_class>( _rejectionConstants[index]( i ) ) ) - c.real_val( carl::convert<Number, mpq_class>( fullOffset( i ) ) );

            for ( unsigned j = 0; j < fullLinTransform.cols(); j++ ) {
                constant = constant * variables.at(j * 3 + 2);
                if ( fullLinTransform( i, j ) != carl::constant_zero<Number>::get() ) {
                    z3::expr summand( c );
                    summand = ( c.real_val( carl::convert<Number, mpq_class>( fullLinTransform( i, j ) ) ) ) * variables.at( j*3 ) * variables.at( j*3 +1);
                    for (unsigned k = 0; k < _constraints.cols(); k++ ){
                        if(k != j){
                            summand = summand * variables.at(k * 3 + 2);
                        }
                    }
                    constraint = constraint + summand;
                }
            }
            
            disjunction = disjunction || (constraint > constant);   
        }

        formula = formula && disjunction;
    }  
    std::cout << "Forumla: \n" << formula << "\n" << "Objective:\n" << objective << std::endl;
    return std::make_pair( formula, objective );
}

template <typename Number>
static std::pair<z3::expr, z3::expr> createFormula( const matrix_t<Number>& _constraints, const vector_t<Number> _constants, const std::vector<carl::Relation>& relations, const vector_t<Number>& _objective, z3Context& c, std::vector<z3::expr>& variables ) {
    z3::expr formula( c );
    z3::expr objective( c );
    objective = c.int_val( 0 );
    formula = c.bool_val( true );
    for ( unsigned i = 1; i <= _constraints.cols(); ++i ) {
        std::string name = "x_" + std::to_string( i );
        variables.push_back( c.real_const( name.c_str() ) );
    }

    for ( unsigned colIndex = 0; colIndex < _constraints.cols(); ++colIndex ) {
        if ( _objective( colIndex ) != carl::constant_zero<Number>::get() ) {
            z3::expr var = variables.at( colIndex );
            z3::expr coeff = c.real_val( carl::convert<Number, mpq_class>( _objective( colIndex ) ) );
            assert( coeff.is_arith() );
            z3::expr tmp = var * coeff;
            objective = objective + tmp;
        }
    }

    for ( unsigned i = 0; i < _constraints.rows(); ++i ) {
        z3::expr constraint( c );
        constraint = c.int_val( 0 );
        for ( unsigned j = 0; j < _constraints.cols(); ++j ) {
            if ( _constraints( i, j ) != carl::constant_zero<Number>::get() ) {
                constraint = constraint + variables.at( j ) * ( c.real_val( carl::convert<Number, mpq_class>( _constraints( i, j ) ) ) );
            }
        }
        z3::expr constant = c.real_val( carl::convert<Number, mpq_class>( _constants( i ) ) );
        switch ( relations[i] ) {
            case carl::Relation::LEQ:
                constraint = constraint <= constant;
                break;
            case carl::Relation::GEQ:
                constraint = constraint >= constant;
                break;
            case carl::Relation::EQ:
                constraint = constraint == constant;
                break;
            default:
                assert( false );
                break;
        }
        formula = formula && constraint;
    }

    return std::make_pair( formula, objective );
}

template <typename Number>
static z3::expr createFormula( const ConstraintsT<Number>& constraint_conjunction, z3Context& c, std::vector<z3::expr>& variables ) {
    z3::expr formula( c );

    for ( const auto& constraint : constraint_conjunction ) {
        formula = formula && createFormula( constraint, variables );
    }
    return formula;
}

template <typename Number>
Number z3ResToNumber( z3::context& c, z3::ast& resZ3 ) {
    int64_t* p = new int64_t;
    uint64_t* q = new uint64_t;
    
    Number resNumber;
    if (Z3_get_numeral_int64(c, Z3_get_numerator(c, resZ3), p) && Z3_get_numeral_uint64(c, Z3_get_denominator(c, resZ3), q)){
        //Try to fit numerator and denomiator into 64-bit (signed/unsigned) ints
        mpq_t resRational;
        mpq_init( resRational );
        mpq_set_si( resRational, *p, *q);
        resNumber = carl::convert<mpq_class, Number>( mpq_class( resRational ) );
        mpq_clear( resRational );
        
        
    } else {
        //Otherwise use a string of arbitary length
        resNumber = carl::convert<mpq_class, Number>(mpq_class(Z3_get_numeral_string(c, resZ3)));        
    }

    delete p;
    delete q;
    return resNumber;
}

}  // namespace hypro

#endif
