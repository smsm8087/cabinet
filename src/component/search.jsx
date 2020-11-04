import React, { Component } from 'react'
import products from "../assets/images/PRODUCTS.png";

import history from '../route/history'

class Search extends Component {
  constructor(props) {
    super(props);
    this.state = {
      searchValue: '',
    }
    this.handleChange = this.handleChange.bind(this);
  }

  handleChange(event) {
    this.setState({
      searchValue: event.target.value
    });
  }

  render(){

    const handleSearch = (e) => {
      history.push(
        '/services',
        this.state,
        console.log(this.state)
      )
    }

    return(
      <React.Fragment>
        <div className= "Banner">
          <span className="search-box">
            <input
              type="text"
              value={this.state.searchValue}
              onChange={this.handleChange}
              placeholder="구를 검색해주세요."
              name="search"
            />
            <button
              className="icon-search"
              onClick={(e) => handleSearch(e)}
            >
              조회
            </button>
          </span>
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

export default Search