-- Quickly generate a template of files that have been changed/added

local PATTERNS = {
    MODIFIED = "M%s%s[%a/_%.]+",
    TO_BE_ADDED = "A%s%s[%a/_%.]+"
}

local p = io.popen("git status --porcelain")
if not p then
    print("Error while getting output of `git status --porcelain`, maybe git is not on PATH?")
    return
end
p:flush()
local out = p:read("*a")

local template_buf = {
    src = {},
    tests = {},
    include = {},
    other = {}
}

local function add_m(t, path)
    table.insert(t, {
        path=path,
        type="M"
    })
end
local function add_a(t, path)
    table.insert(t, {
        path=path,
        type="A"
    })
end
for i in string.gmatch(out, PATTERNS.MODIFIED) do
    i = i:gsub("M%s%s", "")

    if i:find("include/") then
        add_m(template_buf.include, i)
    elseif i:find("src/") then
        add_m(template_buf.src, i)
    elseif i:find("tests/") then
        add_m(template_buf.tests, i)
    else
        add_m(template_buf.other, i)
    end
end
for i in out:gmatch(PATTERNS.TO_BE_ADDED) do
    i = i:gsub("A%s%s", "")

    if i:find("include/") then
        add_a(template_buf.include, i)
    elseif i:find("src/") then
        add_a(template_buf.src, i)
    elseif i:find("tests/") then
        add_a(template_buf.tests, i)
    else
        add_a(template_buf.other, i)
    end
end

local changelog_file = "# LuaCXX changelog\n"

changelog_file = changelog_file .. "Version : " .. arg[1] .. "\n" .. "Current Date : " .. arg[2] .."\n\n"

local function add_supersection(header, content)
    changelog_file = changelog_file .. header .. "\n\n"
    local changed = {}
    local added = {}
    for k, v in pairs(content) do
        local tmp = ""
        if string.find(v.path, "CHANGELOG.md", nil, true) then
            goto continue
        end
        if v.type == "M" then
            tmp = tmp .. "#### Changed `" .. v.path .. "`\n"
            table.insert(changed, tmp)
        elseif v.type == "A" then
            tmp = tmp .. "#### Added `" .. v.path .. "`\n"
            table.insert(added, tmp)
        end
        ::continue::
    end
    changelog_file = changelog_file .. "### Changed files\n\n"
    for k, v in pairs(changed) do
        changelog_file = changelog_file .. v
    end
    changelog_file = changelog_file .. "\n"

    changelog_file = changelog_file .. "### Added files\n\n"
    for k, v in pairs(added) do
        changelog_file = changelog_file .. v
    end
    changelog_file = changelog_file .. "\n"
end

add_supersection("## `tests/`", template_buf.tests)
add_supersection("## `src/`", template_buf.src)
add_supersection("## `include/`", template_buf.include)
add_supersection("## Other", template_buf.other)

local f = io.open("CHANGELOG.md", "w")
if not f then
    print("Error while trying to create CHANGELOG.md file.")
    return
end
f:write(changelog_file)
f:close()
