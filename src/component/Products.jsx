import React, { Component } from 'react'
// import {NavLink} from "react-router-dom";

class Products extends Component {

  render() {
    return (
      <React.Fragment>
        <div className="about-box">
          <div className="about-title">
            <div>Member</div>
            <hr/>
          </div>
          <div className="about-member">
            <ul>
              <li>김도형</li>
              <li>손성현</li>
              <li>정효경</li>
              <li>박시원</li>
            </ul>
          </div>
        </div>
      </React.Fragment>
    )
  }

}

export default Products