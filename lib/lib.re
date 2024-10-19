[%%mel.raw "require('isomorphic-fetch')"];

module Route = {
  // TODO: might need to rethink this since the types for make of response doesn't exist
  type handler = Fetch.request => Js.Promise.t(Fetch.response);

  type route = {
    method: string,
    pattern: string,
    dynamic: bool,
  };

  type routes = list(route);

  let make = (method: string, pattern: string): route => {
    method,
    pattern,
    dynamic: false,
  };

  let add = (route: route, routes: routes) => [route, ...routes];

  let find = (url: string, method: string, routes: routes): option(route) => {
    let searchableList = List.rev(routes);
    let staticMatch =
      List.find_opt(
        route => route.method == method && route.pattern == url,
        searchableList,
      );
    switch (staticMatch) {
    | Some(route) => Some(route)
    | None => None
    };
  };
};