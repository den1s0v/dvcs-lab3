import React, { Component } from "react";
import { hot } from "react-hot-loader/root";

import { NavBar } from "./NavBar";
import { Route } from "react-router-dom"

import { Index } from "./Index";
import { Samples } from "./Samples";

// Commit 1
// Commit 2
class App extends Component {

  render() {
    return (
      <div>
        <NavBar></NavBar>
        <Route path="/" exact component={Index} />
        <Route path="/tasks" component={Samples} />
      </div>
    )
  }
  //commit в своей 1
  //commit в своей 2
}

export default hot(App);