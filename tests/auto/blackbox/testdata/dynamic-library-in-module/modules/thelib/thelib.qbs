import qbs
import qbs.FileInfo

Module {
    Depends { name: "cpp" }
    property string baseDir: FileInfo.cleanPath(FileInfo.joinPaths(path, "..", ".."))
    cpp.rpaths: [product.thelib.baseDir]
    Group {
        name: "thelib dll"
        files: FileInfo.joinPaths(product.thelib.baseDir,
                                  cpp.dynamicLibraryPrefix + "thelib" + cpp.dynamicLibrarySuffix)
        fileTags: ["dynamiclibrary"]
        filesAreTargets: true
    }
    Group {
        name: "thelib dll import"
        condition: qbs.targetOS.contains("windows") && !qbs.toolchain.contains("mingw")
        files: FileInfo.joinPaths(product.thelib.baseDir, "thelib.lib")
        fileTags: ["dynamiclibrary_import"]
        filesAreTargets: true
    }
}
