{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "pipex";
  nativeBuildInputs = with pkgs; [
    clang_12
    # clang12Stdenv
  ];
}
