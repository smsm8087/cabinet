import React, { Component } from 'react'

import Nowongu from "./Nowongu";
import Suwon from "./Suwon";
import Hongdae from "./hongdae";

import Search from './search'

class Services extends Component {
  constructor(props) {
    super(props);
    this.state = {
      value: this.props.history.location.state["searchValue"]
      // searchValue: this.props.searchValue
    }
  }


  render() {

    return (
      <React.Fragment>
        <Search />
        <div>
          {
            this.state.value === null ?
              <div>
                검색어를 입력해주세요.
              </div>
              : ''
          }

          {
            this.state.value === "노원구" ?  <Nowongu /> : ''
          }

          {
            this.state.value === "수원" ? <Suwon /> : ''
          }

          {
            this.state.value === "홍대" ? <Hongdae /> : ''
          }
        </div>
      </React.Fragment>
    )
  }

}

export default Services