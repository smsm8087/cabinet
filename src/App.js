import React, { Component } from 'react'
import Route from './route'
import {BrowserRouter} from 'react-router-dom';
import './assets/css/style.css'

class App extends Component {

  render() {
    return (
      <BrowserRouter>
        <Route />
      </BrowserRouter>
    )
  }
}

export default App;
