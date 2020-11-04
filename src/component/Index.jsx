import React, { Component } from 'react'
import products from "../assets/images/PRODUCTS.png";

import Search from './search'

class Index extends Component {
  constructor(props) {
    super(props);
      //
  }

  render(){

    return(
      <React.Fragment>
        <Search />
        <div className="inputarea-box">
          <div className= "inputarea">
            <img className="a" src= {products} alt =""/>
            <div>
              <h4>부동산 이상패턴 탐지</h4>
              <p>
                이상패턴 탐지 시스템을 이용하여 원하는 아파트의 가격을 예측하고,
                가격변동 그래프와 아파트 관련 뉴스 정보를 통해 이상패턴을 추측할 수 있습니다.
                구 입력 칸에 원하는 구를 입력하면 매물 정보, 관련 뉴스, 예측 가격, 그래프 등을 볼 수 있습니다.
              </p>
            </div>
          </div>
        </div>
      </React.Fragment>
    )
  }

}

// const mapStateToProps = state => {
//   return {
//     searchValue: state.searchValue
//   }
// }
//
// export default (
//   mapStateToProps
// )(Index)

export default Index