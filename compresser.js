const fs = require('fs');
const path = require('path');
const { minify: minifyHTML } = require('html-minifier');
const cleanCSS = require('clean-css');
const UglifyJS = require('uglify-js');
const { optimize: optimizeSVG } = require('svgo');

const sourceDir = './web';
const targetDir = './data';

// 定义支持的文件类型
const supportedExtensions = ['.html', '.css', '.js', '.svg'];

// HTML 最小化选项
const htmlMinifyOptions = {
    collapseWhitespace: true,
    removeComments: true,
    minifyJS: true,
    minifyCSS: true
};

// CSS 最小化实例
const cssMinifier = new cleanCSS();

// JavaScript 最小化函数
function minifyJS(content) {
    const result = UglifyJS.minify(content);
    if (result.error) {
        throw result.error;
    }
    return result.code;
}

// 遍历文件夹，优化和最小化文件
async function optimizeFiles(directory) {
    const files = fs.readdirSync(directory);

    for (const file of files) {
        const filePath = path.join(directory, file);
        const stat = fs.statSync(filePath);

        if (stat.isDirectory()) {
            await optimizeFiles(filePath); // 如果是目录，递归处理
        } else {
            const ext = path.extname(filePath).toLowerCase();

            if (supportedExtensions.includes(ext)) {
                // 读取文件内容
                let content = fs.readFileSync(filePath, 'utf8');

                // 根据文件类型进行最小化和优化处理
                switch (ext) {
                    case '.html':
                        content = minifyHTML(content, htmlMinifyOptions);
                        break;
                    case '.css':
                        content = cssMinifier.minify(content).styles;
                        break;
                    case '.js':
                        content = minifyJS(content);
                        break;
                    case '.svg':
                        content = (await optimizeSVG(content)).data;
                        break;
                    default:
                        break;
                }

                // 将处理后的内容写入目标文件
                const targetFilePath = path.join(targetDir, file);
                fs.writeFileSync(targetFilePath, content, 'utf8');

                console.log(`File optimized and minified: ${filePath}`);
            }
        }
    }
}

// 调用递归函数，开始处理
optimizeFiles(sourceDir)
    .then(() => console.log('All files optimized and minified successfully.'))
    .catch(err => console.error(`Error optimizing files: ${err.message}`));