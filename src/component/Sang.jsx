import React, { Component } from 'react'

import Search from './search'

class Sang extends Component {
  constructor(props) {
    super(props);
    //
  }

  render(){

    return(
      <React.Fragment>
        <Search />
        <div className="table-box">
          <h4 className="table-title">상계주공 16단지</h4>
          <table>
            <tr>
              <th>거래</th>
              <th>종류</th>
              <th>확인일</th>
              <th>매물명</th>
              <th>면적</th>
              <th>동</th>
              <th>층</th>
              <th>매물가(만원)</th>
              <th>연락처</th>
            </tr>
            <tr>
              <td>307</td>
              <td>전세 아파트</td>
              <td>20.10.26</td>
              <td>상계주공16단지</td>
              <td>63/46</td>
              <td>1603</td>
              <td>4/15</td>
              <td>18,000</td>
              <td>다산공인중개사사...02-930-6800</td>
            </tr>
            <tr>
              <td>496</td>
              <td>매매 아파트</td>
              <td>20.10.08</td>
              <td>상계주공16단지</td>
              <td>82/59</td>
              <td>1605</td>
              <td>9/15</td>
              <td>60,000</td>
              <td>파랑새공인중개사...02-937-0011</td>
            </tr>
            <tr>
              <td>620</td>
              <td>매매 아파트</td>
              <td>20.11.02</td>
              <td>상계주공16단지</td>
              <td>82/59</td>
              <td>1605</td>
              <td>9/15</td>
              <td>60,000</td>
              <td>상계공인중개사02-931-0011</td>
            </tr>
            <tr>
              <td>847</td>
              <td>매매 아파트</td>
              <td>20.10.24</td>
              <td>상계주공16단지</td>
              <td>82/59</td>
              <td>1604</td>
              <td>3/15</td>
              <td>53,000</td>
              <td>다산공인중개사사...02-930-6800</td>
            </tr>
            <tr>
              <td>859</td>
              <td>매매 아파트</td>
              <td>20.10.23</td>
              <td>상계주공16단지</td>
              <td>63/46</td>
              <td>1603</td>
              <td>9/15</td>
              <td>44,000</td>
              <td>다산공인중개사사...02-930-6800</td>
            </tr>
          </table>
        </div>
        <div className="image-box">
          <h4>예측 그래표</h4>
          <span className="table-image"></span>
        </div>
      </React.Fragment>
    )
  }
}

export default Sang