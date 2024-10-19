module Route = {
  type route = {
    method: string,
    pattern: string,
    dynamic: bool,
  };

  type routes = list(route);

  let empty = () => [];

  let make = (method: string, pattern: string): route => {
    let urlSplits = String.split_on_char('/', pattern);
    let isDynamic =
      switch (List.find_opt(str => str == "*" || str == "**", urlSplits)) {
      | Some(_str) => true
      | None => false
      };
    let routeDef = {method, pattern, dynamic: isDynamic};
    routeDef;
  };

  let add = (route: route, routes: routes) => [route, ...routes];

  let match =
      (method: string, url: string, ~isDynamic: option(bool)=?, route: route) => {
    let getChar = char =>
      char == "**" ? "(\\w*)" : char == "*" ? "(\\w+)" : char;
    let regexStr =
      String.split_on_char('/', route.pattern)
      |> List.map(getChar)
      |> String.concat("/");

    switch (isDynamic) {
    | Some(isDynx) =>
      isDynx
        ? Js.Re.fromString(regexStr) |> Js.Re.test(~str=url)
        : method == route.method && url == route.pattern
    | None => method == route.method && url == route.pattern
    };
  };

  let find = (url: string, method: string, routes: routes): option(route) => {
    let searchableList = List.rev(routes);
    List.find_opt(route => match(method, url, route, ~isDynamic=route.dynamic), searchableList);
  };
};
