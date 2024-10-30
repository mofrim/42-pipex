{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "pipex";
  nativeBuildInputs = with pkgs; [
    clang-tools
    clang_12
    # clang12Stdenv
  ];
}
