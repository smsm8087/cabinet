import React, { Component } from 'react'

// 페이지 이동용. react에서는 a태그를 사용 X
// 브라우저나 개발자 메뉴에서는 a태그로 나타남
import { NavLink } from 'react-router-dom'

class Header extends Component {

  render() {

    return (
      <React.Fragment>
        <header>

          <div className= "mainTitle">
            <ul>
              <li>
                <NavLink to="/" exact={true}>HOME</NavLink>
              </li>
              <li>
                <NavLink to="/services">SERVICES</NavLink>
              </li>
              <li>
                <NavLink to="/about">ABOUT US</NavLink>
              </li>
            </ul>
          </div>

        </header>
      </React.Fragment>
    )
  }

}

export default Header