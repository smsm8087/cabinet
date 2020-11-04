import React from 'react'
import { Router, Route, Switch } from 'react-router-dom'
import history from './history'

import Header from '../component/default/header'
import Footer from '../component/default/footer'

import Index from '../component/Index'
import Products from '../component/Products';
import Services from '../component/Services';

const Routes = ({ auth }) => {
  return (

    <Router
      history={history}
    >
      <Header />
      <Switch>

        <Route exact path='/' component={Index} />
        <Route exact path='/about' component={Products} />
        <Route exact path='/services' component={Services} />

      </Switch>
      <Footer />

    </Router>

  )
}

export default Routes