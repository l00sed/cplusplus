ostream& bold_on( ostream& os )
{
  return os << "\e[1m";
}

ostream& bold_off( std::ostream& os )
{
  return os << "\e[0m";
}
